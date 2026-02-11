zx_yubikey_authn(const char* path, char* uid, const char* passw)
{
  unsigned char buf[256];
  unsigned char pw_buf[256];
  unsigned char pw_hash[120];
  yubikey_token_st yktok;
  int len = strlen(uid);

  strcpy((char*)pw_hash, uid + len - 32);
  uid[len - 32] = 0;
  D("yubikey user(%s) ticket(%s)", uid, pw_hash);

  snprintf((char*)buf, sizeof(buf)-1, "%s" ZXID_UID_DIR "%s", path, uid);
  buf[sizeof(buf)-1] = 0;
  len = read_all(sizeof(pw_buf), (char*)pw_buf, "ykspent", 0, "%s/.ykspent/%s", buf, pw_hash);
  if (len) {
    ERR("The One Time Password has already been spent. ticket(%s%s) buf(%.*s)", uid, pw_hash, len, pw_buf);
    return 0;
  }
  if (!write_all_path_fmt("ykspent", sizeof(pw_buf), (char*)pw_buf, "%s/.ykspent/%s", (char*)buf, (char*)pw_hash, "1"))
    return 0;

  len = read_all(sizeof(pw_buf), (char*)pw_buf, "ykaes", 1, "%s/.yk", buf);
  D("buf    (%s) got=%d", pw_buf, len);
  if (len < 32) {
    ERR("User's %s/.yk file must contain aes128 key as 32 hexadecimal characters. Too few characters %d ticket(%s)", uid, len, pw_hash);
    return 0;
  }
  if (len > 32) {
    INFO("User's %s/.yk file must contain aes128 key as 32 hexadecimal characters. Too many characters %d ticket(%s). Truncating.", uid, len, pw_hash);
    len = 32;
    pw_buf[len] = 0;
  }
  zx_hexdec((char*)pw_buf, (char*)pw_buf, len, hex_trans);
  ZERO(&yktok, sizeof(yktok));
  zx_hexdec((void*)&yktok, (char*)pw_hash, 32, ykmodhex_trans);
  yubikey_aes_decrypt((void*)&yktok, pw_buf);
  D("internal uid %02x %02x %02x %02x %02x %02x counter=%d 0x%x timestamp=%d (hi=%x lo=%x) use=%d 0x%x rnd=0x%x crc=0x%x", yktok.uid[0], yktok.uid[1], yktok.uid[2], yktok.uid[3], yktok.uid[4], yktok.uid[5], yktok.ctr, yktok.ctr, (yktok.tstph << 16) | yktok.tstpl, yktok.tstph, yktok.tstpl, yktok.use, yktok.use, yktok.rnd, yktok.crc);

  if (!yubikey_crc_ok_p((unsigned char*)&yktok)) {
    ERR("yubikey ticket validation failure %d", 0);
    return 0;
  }
  return 1;
}

handle_auth (fs_backend *be,
                                    fs_segment segment,
                                    unsigned int length,
                                    unsigned char *content)
{
  md5_state_t md5;

  if (length <= 16) {
    fs_error(LOG_ERR, "auth(%d) missing kbname", segment);
    return fsp_error_new(segment, "missing kbname");
  }

  if (strncmp(be->db_name, (char *) content + 16, length - 16)) {
    fs_error(LOG_ERR, "auth(%d) wrong kbname", segment);
    return fsp_error_new(segment, "wrong kbname");
  }

  if (be->salt) {
    unsigned char data[20], hash[16];
    char string[33];
    memcpy(data, (&be->salt), sizeof(be->salt));

    memcpy(data + 4, content, 16);
    md5_init(&md5);
    md5_append(&md5, data, sizeof(data));
    md5_finish(&md5, hash);
    sprintf(string, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7],
            hash[8], hash[9], hash[10], hash[11], hash[12], hash[13], hash[14], hash[15]);

    if (strcmp(string, be->hash)) {
      fs_error(LOG_ERR, "auth(%d) invalid password", segment);
      return fsp_error_new(segment, "invalid password");
    }
  }


  unsigned char *reply = message_new(FS_DONE_OK, 0, sizeof(feature_string));
  memcpy(reply + FS_HEADER, feature_string, sizeof(feature_string));
  return reply;
}

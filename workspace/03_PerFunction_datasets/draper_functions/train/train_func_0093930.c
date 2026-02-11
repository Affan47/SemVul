pack_info(Protocol *protocol)
{
  char buf1[256], buf[22];
  String tmp(buf1, sizeof(buf1), log_cs);
  tmp.length(0);
  tmp.append(new_log_ident, ident_len);
  tmp.append(STRING_WITH_LEN(";pos="));
  tmp.append(llstr(pos,buf));
  protocol->store(tmp.ptr(), tmp.length(), &my_charset_bin);
}

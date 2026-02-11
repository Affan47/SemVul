japi_add_grammar(int sd, char *prefixpath)
{

  if (check_grammar_path(prefixpath) < 0) return;


  snprintf(buf, MAXLINELEN, "ADDGRAM %s\n", prefixpath);
  do_send(sd, buf);
  send_grammar(sd, prefixpath);
}

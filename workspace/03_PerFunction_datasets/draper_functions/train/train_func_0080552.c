dump_sig(struct signature *sig) {

  u32 i;

  DEBUG("\n=== New signature loaded ===\n");
  DEBUG("  id        = %d\n", sig->id);
  DEBUG("  severity  = %d\n", sig->severity);
  DEBUG("  content # = %d\n", sig->content_cnt);

  for (i=0; i<sig->content_cnt; i++) {
    DEBUG("  %d. match_str     = %s\n", i, sig->content[i]->match_str);
    DEBUG("  %d. type          = %s\n", i, sig->content[i]->type ? "REGEX" : "STRING");
    DEBUG("  %d. offset        = %d\n", i, sig->content[i]->offset);
    DEBUG("  %d. depth         = %d\n", i, sig->content[i]->depth);
    DEBUG("  %d. position      = %d\n", i, sig->content[i]->distance);
    DEBUG("  %d. nocase        = %d\n", i, sig->content[i]->nocase);
    DEBUG("  %d. no            = %d\n", i, sig->content[i]->no);

  }

  if (sig->memo)
    DEBUG("  memo     = %s\n", sig->memo);
  if (sig->mime)
    DEBUG("  mime     = %s\n", sig->mime);
  if (sig->rcode)
    DEBUG("  code     = %d\n", sig->rcode);

  DEBUG("  depend    = %d\n", sig->depend ? sig->depend->id : 0);
  DEBUG("  header    = %s\n", sig->header ? (char*)sig->header : (char*)"");

  switch (sig->proto) {
    case '0':
      DEBUG("  proto    = HTTP/HTTPS\n");
      break;
    case PROTO_HTTP:
      DEBUG("  proto    = HTTP\n");
      break;
    case PROTO_HTTPS:
      DEBUG("  proto    = HTTPS\n");
  }
}

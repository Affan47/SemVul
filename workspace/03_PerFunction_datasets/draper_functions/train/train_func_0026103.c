save_pivots(FILE* f, struct pivot_desc* cur) {

  u32 i;

  if (cur->req) {
    u8* url = serialize_path(cur->req, 1, 1);

    fprintf(f, "%s %s ", cur->req->method ? cur->req->method : (u8*)"GET",
           js_escape(url, 0));

    ck_free(url);

    fprintf(f, "name=%s ", js_escape(cur->name, 1));

    switch (cur->type) {
      case PIVOT_SERV:     fprintf(f, "type=serv "); break;
      case PIVOT_DIR:      fprintf(f, "type=dir "); break;
      case PIVOT_FILE:     fprintf(f, "type=file "); break;
      case PIVOT_PATHINFO: fprintf(f, "type=pathinfo "); break;
      case PIVOT_VALUE:    fprintf(f, "type=value "); break;
      case PIVOT_UNKNOWN:  fprintf(f, "type=unknown "); break;
      case PIVOT_PARAM:    fprintf(f, "type=param "); break;
      default:             fprintf(f, "type=??? ");
    }

    switch (cur->linked) {
      case 0:  fprintf(f, "linked=no "); break;
      case 1:  fprintf(f, "linked=maybe "); break;
      default: fprintf(f, "linked=yes ");
    }


    if (!cur->linked && !no_parse && !cur->missing)
      problem(PROB_HIDDEN_NODE, cur->req, cur->res, 0, cur, 0);


    fprintf(f, "browsers=%d ", cur->browsers ? cur->browsers : browser_type);


    switch (cur->browser) {
      case 0:  fprintf(f, "browser_used=FAST "); break;
      case 1:  fprintf(f, "browser_used=MSIE "); break;
      case 2:  fprintf(f, "browser_used=FFOX "); break;
      case 4:  fprintf(f, "browser_used=PHONE "); break;
      default: fprintf(f, "browser_used=??? ");
    }

    if (cur->res)
      fprintf(f, "dup=%u %s%scode=%u len=%u notes=%u sig=0x%x\n", cur->dupe,
             cur->bogus_par ? "bogus " : "",
             cur->missing ? "returns_404 " : "",
             cur->res->code, cur->res->pay_len,
             cur->issue_cnt, cur->pv_sig);
    else
      fprintf(f, "not_fetched\n");


  }

  for (i=0;i<cur->child_cnt;i++) save_pivots(f, cur->child[i]);

}

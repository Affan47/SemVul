result_pass1_final(Recog *recog, void *dummy)
{
  int i;
  RecogProcess *r;
  boolean multi;

  if (out1_never) return;

  if (recog->process_list->next != NULL) multi = TRUE;
  else multi = FALSE;

  for(r=recog->process_list;r;r=r->next) {
    if (! r->live) continue;
    if (r->result.status < 0) continue;

    if (multi) {
      module_send(module_sd, "<RECOGOUT ID=\"SR%02d\" NAME=\"%s\">\n", r->config->id, r->config->name);
    } else {
      module_send(module_sd, "<RECOGOUT>\n");
    }
    if (out1_score) {
      module_send(module_sd, "  <SHYPO PASS=\"1\" SCORE=\"%f\">\n", r->result.pass1.score);
    } else {
      module_send(module_sd, "  <SHYPO PASS=\"1\">\n", r->result.pass1.score);
    }
    for (i=0;i<r->result.pass1.word_num;i++) {
      module_send(module_sd, "    <WHYPO");
      msock_word_out1(r->result.pass1.word[i], r);
      module_send(module_sd, "/>\n");
    }
    module_send(module_sd, "  </SHYPO>\n</RECOGOUT>\n.\n");
  }
}

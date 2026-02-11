result_sentence_free(RecogProcess *r)
{
  int i;
  SentenceAlign *a, *atmp;
  if (r->result.sent) {
    for(i=0;i<r->result.sentnum;i++) {
      a = r->result.sent[i].align;
      while(a) {
	atmp = a->next;
	result_align_free(a);
	a = atmp;
      }
    }
    free(r->result.sent);
    r->result.sent = NULL;
  }
}

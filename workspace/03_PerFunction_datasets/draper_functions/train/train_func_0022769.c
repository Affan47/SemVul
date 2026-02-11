result_sentence_malloc(RecogProcess *r, int num)
{
  int i;
  r->result.sent = (Sentence *)mymalloc(sizeof(Sentence) * num);
  for(i=0;i<num;i++) r->result.sent[i].align = NULL;
  r->result.sentnum = 0;
}

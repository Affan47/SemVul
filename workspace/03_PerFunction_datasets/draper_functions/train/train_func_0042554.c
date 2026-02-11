HTMLTDInsert(li, env, p)
HTMLInfo li;
HTMLEnv env;
MLElement p;
{
  HTMLEnv c;
  HTMLTagID tid;

  for (c = (HTMLEnv)GListGetHead(li->envstack); c != NULL;
       c = (HTMLEnv)GListGetNext(li->envstack))
  {
    tid = HTMLTagToID(c->tag);
    if (tid == TAG_TABLE || tid == TAG_TR) break;
  }

  if (c == NULL) return(HTMLInsertReject);
  else if (tid == TAG_TABLE) HTMLStartEnv(li, TAG_TR, NULL);
  else HTMLPopEnv(li, TAG_TR);

  return(HTMLInsertOK);
}

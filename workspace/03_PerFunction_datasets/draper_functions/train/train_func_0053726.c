fixupChapter(ulonglong adj, struct Chapter *ch) {
  unsigned i;

  if (ch->Start != 0)
    ch->Start -= adj;
  if (ch->End != 0)
    ch->End -= adj;

  for (i=0;i<ch->nChildren;++i)
    fixupChapter(adj,&ch->Children[i]);
}

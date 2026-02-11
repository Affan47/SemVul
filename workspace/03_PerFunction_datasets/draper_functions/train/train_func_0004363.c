readZuker(struct ReadSeqVars *V)
{


  while (!V->allDone) {
    mygetline(V);
    strcpy(V->seqid, (V->s)+6);
    readLoop(0, false, endZuker, V);
    if (!V->allDone) {
      while (!(feof(V->f) |
        ((*V->s != '\0') & (*V->s == '('))))
          mygetline(V);
      }
    if (feof(V->f)) V->allDone = true;
  }
}

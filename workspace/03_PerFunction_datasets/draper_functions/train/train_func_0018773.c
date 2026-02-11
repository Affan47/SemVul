MR_alphaBetaTraceReport(void)
#else
void MR_alphaBetaTraceReport()
#endif
{
  int       i;

  if (! AlphaBetaTrace) return;

  MR_AlphaBetaMessageCount++;

  fprintf(output,"\n");
  fprintf(output,"#if 0\n");
  fprintf(output,"\n");
  fprintf(output,"Trace of references leading to attempt to compute the follow set of\n");
  fprintf(output,"alpha in an \"(alpha)? beta\" block. It is not possible for antlr to\n");
  fprintf(output,"compute this follow set because it is not known what part of beta has\n");
  fprintf(output,"already been matched by alpha and what part remains to be matched.\n");
  fprintf(output,"\n");
  fprintf(output,"Rules which make use of the incorrect follow set will also be incorrect\n");
  fprintf(output,"\n");

  MR_backTraceDumpItemReset();

  for (i=0; i < MR_BackTraceStack.count ; i++) {
     MR_backTraceDumpItem(output,0,(Node *) MR_BackTraceStack.data[i]);
     if (i < MR_BackTraceStack.count-1) {
        MR_markCompromisedRule( (Node *) MR_BackTraceStack.data[i]);
     };
  };
  fprintf(output,"\n");
  fprintf(output,"#endif\n");
}

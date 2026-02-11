s48_initializing_gc_root(void)
{
  long expr_79X;
  long expr_78X;
  long expr_77X;
  long expr_76X;
  long expr_75X;
 {  if ((SinitializingPS)) {
    expr_75X = s48_trace_value((Sstartup_procedureS));
    Sstartup_procedureS = expr_75X;
    expr_76X = s48_trace_value((SsymbolsS));
    SsymbolsS = expr_76X;
    expr_77X = s48_trace_value((Simported_bindingsS));
    Simported_bindingsS = expr_77X;
    expr_78X = s48_trace_value((Sexported_bindingsS));
    Sexported_bindingsS = expr_78X;
    expr_79X = s48_trace_value((Sresumer_recordsS));
    Sresumer_recordsS = expr_79X;
    return;}
  else {
    return;}}
}

add_wacc(WCHMM_INFO *wchmm, int node, LOGPROB a, int arc)
{
  if (arc == node) {
    wchmm->self_a[node] = a;
  } else if (arc == node + 1) {
    wchmm->next_a[node] = a;
  } else {
    add_ac(wchmm, node, a, arc);
  }
}

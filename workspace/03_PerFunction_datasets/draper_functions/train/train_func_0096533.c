same_cycle(cycle *s_cyc1, cycle *s_cyc2 )
{
  int e, eb;
  short int same;

  if ( s_cyc1->length != s_cyc2->length ) return(FALSE);

  same = TRUE;
  for ( e = 0; e < s_cyc1->length; e++ ) {
    if ( s_cyc1->edge_list[e] != s_cyc2->edge_list[e] ) {
      same = FALSE;
      break;
    }
  }
  if ( same ) return(TRUE);

  same = TRUE;
  for ( e = 0, eb = s_cyc2->length - 1; e < s_cyc1->length; e++, eb-- ) {
    if ( s_cyc1->edge_list[e] != s_cyc2->edge_list[eb] ) {
      same = FALSE;
      break;
    }
  }
  if ( same ) return(TRUE);
  return(FALSE);
}

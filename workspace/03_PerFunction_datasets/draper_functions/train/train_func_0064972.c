check_for_el(const ESL_DSQ *ax, const ESL_ALPHABET *abc, const int *used_el, const int *nxt_mi, const int *nxt_el, int i0, int j0, int *ret_goto_el, int *ret_i, int *ret_j)
{
  int i, j, i2;
  int goto_el = FALSE;

  if(nxt_mi[i0-1] > nxt_el[i0-1] && nxt_mi[i0-1] > j0 && nxt_el[i0-1] <= j0) {


    i = i0;
    j = j0;
    while(esl_abc_XIsGap(abc, ax[i]) && i <= j0) i++;
    while(esl_abc_XIsGap(abc, ax[j]) && j >= i0) j--;
    if(i > j0 || (! used_el[i])) goto ERROR;
    if(j < i0 || (! used_el[j])) goto ERROR;


    for(i2 = i; i2 <= j; i2++) if(! used_el[i2]) break;
    if(i2 == j+1) goto_el = TRUE;

  }

  *ret_goto_el = goto_el;
  if(goto_el) *ret_i = i;
  else        *ret_i = 0;
  if(goto_el) *ret_j = j;
  else        *ret_j = 0;

  return eslOK;

 ERROR:
  *ret_goto_el = FALSE;
  *ret_i       = 0;
  *ret_j       = 0;
  return eslEINVAL;
}

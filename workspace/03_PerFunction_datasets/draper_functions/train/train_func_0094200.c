comb_vect_p (state_ainsn_table_t tab)
{
  return  (2 * VEC_length (vect_el_t, tab->full_vect)
           > 5 * VEC_length (vect_el_t, tab->comb_vect));
}

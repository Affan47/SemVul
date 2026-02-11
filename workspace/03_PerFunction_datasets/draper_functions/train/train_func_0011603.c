free_slot(const int iter_c, pnt_info_t *slot_p,
			  pnt_info_t **used_pp, pnt_info_t **free_pp)
{
  pnt_info_t	*this_p, *prev_p;

  if (verbose_b) {
    (void)printf("%d: free'd %d bytes from slot %d (%#lx)\n",
		 iter_c + 1, slot_p->pi_size, slot_p - pointer_grid,
		 (long)slot_p->pi_pnt);
  }

  slot_p->pi_pnt = NULL;


  for (this_p = *used_pp, prev_p = NULL;
       this_p != NULL;
       prev_p = this_p, this_p = this_p->pi_next) {
    if (this_p == slot_p) {
      break;
    }
  }
  if (prev_p == NULL) {
    *used_pp = slot_p->pi_next;
  }
  else {
    prev_p->pi_next = slot_p->pi_next;
  }

  slot_p->pi_next = *free_pp;
  *free_pp = slot_p;
}

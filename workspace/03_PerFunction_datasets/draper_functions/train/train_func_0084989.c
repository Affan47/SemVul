add_mem_for_addr (cselib_val *addr_elt, cselib_val *mem_elt, rtx x)
{
  struct elt_loc_list *l;


  for (l = mem_elt->locs; l; l = l->next)
    if (MEM_P (l->loc)
	&& CSELIB_VAL_PTR (XEXP (l->loc, 0)) == addr_elt)
      {
	promote_debug_loc (l);
	return;
      }

  addr_elt->addr_list = new_elt_list (addr_elt->addr_list, mem_elt);
  mem_elt->locs
    = new_elt_loc_list (mem_elt->locs,
			replace_equiv_address_nv (x, addr_elt->val_rtx));
  if (mem_elt->next_containing_mem == NULL)
    {
      mem_elt->next_containing_mem = first_containing_mem;
      first_containing_mem = mem_elt;
    }
}

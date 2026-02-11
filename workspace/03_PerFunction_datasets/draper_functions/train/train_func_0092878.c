frag_offset_fixed_p (const fragS *frag1, const fragS *frag2, offsetT *offset)
{
  const fragS *frag;
  offsetT off;


  off = frag1->fr_address - frag2->fr_address;
  if (frag1 == frag2)
    {
      *offset = off;
      return TRUE;
    }


  frag = frag1;
  while (frag->fr_type == rs_fill)
    {
      off += frag->fr_fix + frag->fr_offset * frag->fr_var;
      frag = frag->fr_next;
      if (frag == NULL)
	break;
      if (frag == frag2)
	{
	  *offset = off;
	  return TRUE;
	}
    }


  off = frag1->fr_address - frag2->fr_address;
  frag = frag2;
  while (frag->fr_type == rs_fill)
    {
      off -= frag->fr_fix + frag->fr_offset * frag->fr_var;
      frag = frag->fr_next;
      if (frag == NULL)
	break;
      if (frag == frag1)
	{
	  *offset = off;
	  return TRUE;
	}
    }

  return FALSE;
}

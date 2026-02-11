same_attr_p (dw_attr_ref at1, dw_attr_ref at2, int *mark)
{
  if (at1->dw_attr != at2->dw_attr)
    return 0;


  if (at1->dw_attr == DW_AT_producer)
    return 1;

  return same_dw_val_p (&at1->dw_attr_val, &at2->dw_attr_val, mark);
}

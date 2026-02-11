iterate_for_kind (pIIR_Declaration d, void *cl)
{
  IR_Kind &basic_k = *(IR_Kind *)cl;
  IR_Kind this_k = d->kind();

  if (basic_k == IR_INVALID)
    basic_k = this_k;
  else if (basic_k != this_k && !tree_is (this_k, basic_k))
    {
      while (!tree_is(basic_k, this_k))
	this_k = tree_base (this_k);
      basic_k = this_k;
    }
}

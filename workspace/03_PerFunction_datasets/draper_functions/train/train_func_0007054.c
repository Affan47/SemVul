p_symbol_data(Symbol_data s)
{
  if (s != NULL)
    printf("%s/%d, sn=%d, mace_sn=%d, base=%d, type=%d, attribute=%d.\n",
	   sn_to_str(s->sn), s->arity,
	   s->sn, s->mace_sn, s->base, s->type, s->attribute);
}

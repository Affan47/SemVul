arg_ep(struct spq *jp, const struct argop *ao)
{
	jp->spq_end = ao->ao_un.ao_ulong != 0? ao->ao_un.ao_ulong - 1: LOTSANDLOTS;
	return  1;
}

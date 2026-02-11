ITR_isT(tkitr_t *itr, knh_FisTerm f)
{
	return (ITR_hasNext(itr) && f(ITR_tk(itr)));
}

e_jumps(etmp)
struct entity *etmp;
{
	int tmp = 4;

	if (is_u(etmp)? (Sleeping || Fumbling) :
		        (!etmp->emon->mcanmove || etmp->emon->msleeping ||
			 !etmp->edata->mmove   || etmp->emon->wormno))
		return(FALSE);

	if (is_u(etmp)? Confusion : etmp->emon->mconf)
		tmp -= 2;

	if (is_u(etmp)? Stunned : etmp->emon->mstun)
		tmp -= 3;

	if (is_db_wall(etmp->ex, etmp->ey))
		tmp -= 2;

#ifdef D_DEBUG
	pline("%s to jump (%d chances in 10)", E_phrase(etmp, "try"), tmp);
#endif
	return((boolean)((tmp >= rnd(10))? TRUE : FALSE));
}

setethertypeent(int f)
{
	if (etherf == NULL)
		etherf = fopen(_PATH_ETHERTYPES, "r");
	else
		rewind(etherf);
	ethertype_stayopen |= f;
}

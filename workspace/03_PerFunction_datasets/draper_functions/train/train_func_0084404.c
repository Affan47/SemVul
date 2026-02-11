xdico_sasl_capa_match_p(const char *mech, const char *capa)
{
    int i;

    for (i = 0; i < DICO_ARRAY_SIZE(mech_to_capa_table); i++)
	if (c_strcasecmp(mech_to_capa_table[i][0], mech) == 0)
	    return c_strcasecmp(mech_to_capa_table[i][1], capa) == 0;

    if (*capa == 'x')
	return c_strcasecmp(mech, capa + 1) == 0;
    return 0;
}

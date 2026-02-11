str_scat(STR *dstr, STR *sstr)
{
    if (!(sstr->str_pok))
	str_2ptr(sstr);
    if (sstr)
	str_ncat(dstr,sstr->str_ptr,sstr->str_cur);
}

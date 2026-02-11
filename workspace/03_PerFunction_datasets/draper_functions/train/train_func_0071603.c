set_string_option_global(opt_idx, varp)
    int		opt_idx;
    char_u	**varp;
{
    char_u	**p, *s;


    if (options[opt_idx].var == VAR_WIN)
	p = (char_u **)GLOBAL_WO(varp);
    else
	p = (char_u **)options[opt_idx].var;
    if (options[opt_idx].indir != PV_NONE
	    && p != varp
	    && (s = vim_strsave(*varp)) != NULL)
    {
	free_string_option(*p);
	*p = s;
    }
}

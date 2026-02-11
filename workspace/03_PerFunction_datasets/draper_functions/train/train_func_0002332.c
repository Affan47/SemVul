save_smime_config_vars(struct pine *ps)
{
    struct variable *vreal;
    SAVED_CONFIG_S *vsave, *v;

    vsave = (SAVED_CONFIG_S *)fs_get((V_LAST_VAR+1)*sizeof(SAVED_CONFIG_S));
    memset((void *)vsave, 0, (V_LAST_VAR+1)*sizeof(SAVED_CONFIG_S));
    v = vsave;
    for(vreal = ps->vars; vreal->name; vreal++,v++){
	if(!(smime_related_var(ps, vreal) || vreal==&ps->vars[V_FEATURE_LIST]))
	  continue;

	if(vreal->is_list){
	    int n, i;
	    char **list;

	    if(LVAL(vreal, ew)){

		n = 0;
		list = LVAL(vreal, ew);
		while(list[n])
		  n++;

		v->saved_user_val.l = (char **)fs_get((n+1) * sizeof(char *));
		memset((void *)v->saved_user_val.l, 0, (n+1)*sizeof(char *));
		for(i = 0; i < n; i++)
		  v->saved_user_val.l[i] = cpystr(list[i]);

		v->saved_user_val.l[n] = NULL;
	    }
	}
	else{
	    if(PVAL(vreal, ew))
	      v->saved_user_val.p = cpystr(PVAL(vreal, ew));
	}
    }

    return(vsave);
}

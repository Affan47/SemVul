fluid_synth_get_sfont_by_name(fluid_synth_t* synth, const char *name)
{
	fluid_sfont_t* sfont = NULL;
	fluid_list_t* list;

	fluid_return_val_if_fail (synth != NULL, NULL);
	fluid_return_val_if_fail (name != NULL, NULL);
	fluid_synth_api_enter(synth);

	for (list = synth->sfont_info; list; list = fluid_list_next(list)) {
		sfont = ((fluid_sfont_info_t *)fluid_list_get (list))->sfont;
		if (FLUID_STRCMP(fluid_sfont_get_name(sfont), name) == 0)
			break;
	}

	FLUID_API_RETURN(list ? sfont : NULL);
}

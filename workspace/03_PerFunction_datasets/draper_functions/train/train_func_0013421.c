deserialize_value(pa_sdbm_datum_t key, const pa_sdbm_datum_t value) {

	if(!value.dptr || (size_t)value.dsize<sizeof(Hashfile_value_serialized_prolog))
		return 0;


	Hashfile_value_serialized_prolog prolog;
	memcpy(&prolog, value.dptr, sizeof(prolog));

	if(prolog.version!=HASHFILE_VALUE_SERIALIZED_VERSION
		|| (prolog.time_to_die
			&& (prolog.time_to_die <= time(0)))) {

		remove(key);
		return 0;
	}

	char *input_cstr=value.dptr+sizeof(Hashfile_value_serialized_prolog);
	size_t input_length=value.dsize-sizeof(Hashfile_value_serialized_prolog);

	return new String(input_length? pa_strdup(input_cstr, input_length): 0, String::L_TAINTED);
}

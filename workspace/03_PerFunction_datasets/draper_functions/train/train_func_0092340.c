THX_array_to_hash(pTHX_ AV *array)
{
	HV *hash;
	SV *href;
	I32 alen, i;
	alen = av_len(array);
	if(!(alen & 1))
		throw_constraint_error(
			"odd number of elements in hash constructor");
	hash = newHV();
	href = sv_2mortal(newRV_noinc((SV*)hash));
	for(i = 0; i <= alen; i += 2) {
		SV **key_ptr = av_fetch(array, i, 0);
		STRLEN key_len;
		char *key_str;
		SV *value;
		if(!key_ptr || !sv_is_string(*key_ptr))
			throw_constraint_error("non-string hash key");
		key_str = SvPV(*key_ptr, key_len);
		value = *av_fetch(array, i+1, 0);
		if(!hv_store(hash, key_str, -key_len, SvREFCNT_inc(value), 0))
			SvREFCNT_dec(value);
	}
	return href;
}

put_field(const String& aname, Value *avalue) {
	if(aname.is_empty())
		throw Exception(PARSER_RUNTIME,
			0,
			"hashfile key must not be empty");

	pa_sdbm_t *db=get_db_for_writing();

	time_t time_to_die=0;
	const String *value_string;

	if(HashStringValue *hash=avalue->get_hash()) {
		if(Value *value_value=hash->get(value_name)) {
			if(value_value->get_junction())
				throw Exception(PARSER_RUNTIME,
					0,
					VALUE_NAME" must not be code");

			value_string=&value_value->as_string();

			if(Value *expires=hash->get(expires_name)) {
				if(Value* vdate=expires->as(VDATE_TYPE))
					time_to_die=static_cast<VDate*>(vdate)->get_time();
				else if(double days_till_expire=expires->as_double())
					time_to_die=time(NULL)+(time_t)(60*60*24*days_till_expire);
			}
		} else
			throw Exception(PARSER_RUNTIME,
				&aname,
				"put hash value must contain ."VALUE_NAME);
	} else
		value_string=&avalue->as_string();

	pa_sdbm_datum_t key;
	key.dptr=const_cast<char*>(aname.cstr());
	key.dsize=aname.length();

	pa_sdbm_datum_t value=serialize_value(*value_string, time_to_die);

#ifndef PAIRMAX

#define PAIRMAX 8008
#endif

	if(key.dsize+value.dsize > PAIRMAX)
		throw Exception(PARSER_RUNTIME,
			0,
			"hashfile record length (key+value) exceeds limit (%d bytes)", PAIRMAX);

 	check("pa_sdbm_store", pa_sdbm_store(db, key, value, PA_SDBM_REPLACE));
}

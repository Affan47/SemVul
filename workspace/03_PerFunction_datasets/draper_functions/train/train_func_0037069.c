construct_culture (MonoCultureInfo *this, const CultureInfoEntry *ci)
{
	MonoDomain *domain = mono_domain_get ();

	this->lcid = ci->lcid;
	MONO_OBJECT_SETREF (this, name, mono_string_new (domain, idx2string (ci->name)));
	MONO_OBJECT_SETREF (this, englishname, mono_string_new (domain, idx2string (ci->englishname)));
	MONO_OBJECT_SETREF (this, nativename, mono_string_new (domain, idx2string (ci->nativename)));
	MONO_OBJECT_SETREF (this, win3lang, mono_string_new (domain, idx2string (ci->win3lang)));
	MONO_OBJECT_SETREF (this, iso3lang, mono_string_new (domain, idx2string (ci->iso3lang)));
	MONO_OBJECT_SETREF (this, iso2lang, mono_string_new (domain, idx2string (ci->iso2lang)));


	if (ci->territory > 0)
		MONO_OBJECT_SETREF (this, territory, mono_string_new (domain, idx2string (ci->territory)));
	MONO_OBJECT_SETREF (this, native_calendar_names, create_names_array_idx (ci->native_calendar_names, NUM_CALENDARS));
	this->parent_lcid = ci->parent_lcid;
	this->datetime_index = ci->datetime_format_index;
	this->number_index = ci->number_format_index;
	this->calendar_type = ci->calendar_type;
	this->text_info_data = &ci->text_info;

	return TRUE;
}

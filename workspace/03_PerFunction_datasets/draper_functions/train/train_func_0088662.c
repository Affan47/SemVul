ves_icall_System_Globalization_CultureInfo_construct_number_format (MonoCultureInfo *this)
{
	MonoDomain *domain;
	MonoNumberFormatInfo *number;
	const NumberFormatEntry *nfe;

	MONO_ARCH_SAVE_REGS;

	g_assert (this->number_format != 0);
	if (this->number_index < 0)
		return;

	number = this->number_format;
	nfe = &number_format_entries [this->number_index];

	domain = mono_domain_get ();

	number->readOnly = this->is_read_only;
	number->currencyDecimalDigits = nfe->currency_decimal_digits;
	MONO_OBJECT_SETREF (number, currencyDecimalSeparator, mono_string_new (domain,
			idx2string (nfe->currency_decimal_separator)));
	MONO_OBJECT_SETREF (number, currencyGroupSeparator, mono_string_new (domain,
			idx2string (nfe->currency_group_separator)));
	MONO_OBJECT_SETREF (number, currencyGroupSizes, create_group_sizes_array (nfe->currency_group_sizes,
			GROUP_SIZE));
	number->currencyNegativePattern = nfe->currency_negative_pattern;
	number->currencyPositivePattern = nfe->currency_positive_pattern;
	MONO_OBJECT_SETREF (number, currencySymbol, mono_string_new (domain, idx2string (nfe->currency_symbol)));
	MONO_OBJECT_SETREF (number, naNSymbol, mono_string_new (domain, idx2string (nfe->nan_symbol)));
	MONO_OBJECT_SETREF (number, negativeInfinitySymbol, mono_string_new (domain,
			idx2string (nfe->negative_infinity_symbol)));
	MONO_OBJECT_SETREF (number, negativeSign, mono_string_new (domain, idx2string (nfe->negative_sign)));
	number->numberDecimalDigits = nfe->number_decimal_digits;
	MONO_OBJECT_SETREF (number, numberDecimalSeparator, mono_string_new (domain,
			idx2string (nfe->number_decimal_separator)));
	MONO_OBJECT_SETREF (number, numberGroupSeparator, mono_string_new (domain, idx2string (nfe->number_group_separator)));
	MONO_OBJECT_SETREF (number, numberGroupSizes, create_group_sizes_array (nfe->number_group_sizes,
			GROUP_SIZE));
	number->numberNegativePattern = nfe->number_negative_pattern;
	number->percentDecimalDigits = nfe->percent_decimal_digits;
	MONO_OBJECT_SETREF (number, percentDecimalSeparator, mono_string_new (domain,
			idx2string (nfe->percent_decimal_separator)));
	MONO_OBJECT_SETREF (number, percentGroupSeparator, mono_string_new (domain,
			idx2string (nfe->percent_group_separator)));
	MONO_OBJECT_SETREF (number, percentGroupSizes, create_group_sizes_array (nfe->percent_group_sizes,
			GROUP_SIZE));
	number->percentNegativePattern = nfe->percent_negative_pattern;
	number->percentPositivePattern = nfe->percent_positive_pattern;
	MONO_OBJECT_SETREF (number, percentSymbol, mono_string_new (domain, idx2string (nfe->percent_symbol)));
	MONO_OBJECT_SETREF (number, perMilleSymbol, mono_string_new (domain, idx2string (nfe->per_mille_symbol)));
	MONO_OBJECT_SETREF (number, positiveInfinitySymbol, mono_string_new (domain,
			idx2string (nfe->positive_infinity_symbol)));
	MONO_OBJECT_SETREF (number, positiveSign, mono_string_new (domain, idx2string (nfe->positive_sign)));
}

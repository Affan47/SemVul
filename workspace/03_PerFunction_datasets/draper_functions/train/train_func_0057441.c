read_inner(void *data, size_t nbytes)
{
    long result = deeper->read(data, nbytes);
    if (!result)
    {
	if (checksum_calculated != checksum_given)
	{
	    sub_context_ty sc;
	    sc.var_set_string("File_Name", deeper->name());
	    sc.var_set_string
    	    (
		"Number1",
		nstring::format("%08lX", checksum_given)
	    );
	    sc.var_set_string
    	    (
		"Number2",
		nstring::format("%08lX", checksum_calculated)
	    );
	    sc.fatal_intl
	    (
		i18n("$filename: checksum mismatch ($number1 != $number2)")
	    );

	}
	return 0;
    }
    checksum_calculated = adler32(checksum_calculated, (Bytef *)data, result);
    pos += result;
    return result;
}

dtype_is_binary_string_type(

	ulint	mtype,
	ulint	prtype)
{
	if ((mtype == DATA_FIXBINARY)
	    || (mtype == DATA_BINARY)
	    || (mtype == DATA_BLOB && (prtype & DATA_BINARY_TYPE))) {

		return(TRUE);
	}

	return(FALSE);
}

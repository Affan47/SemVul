assign_debug_assertions(bool newval, bool doit, GucSource source)
{
#ifndef USE_ASSERT_CHECKING
	if (newval)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
			   errmsg("assertion checking is not supported by this build")));
#endif
	return true;
}

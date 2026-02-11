NameToPredefined(const char *name)
{
	int preDef = 0;


	if(!name)
	{
	    UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	    return fp_PageSize::psLetter;
	}

	for(preDef = static_cast<int>(_first_predefined_pagesize_);
	    preDef < static_cast<int>(_last_predefined_pagesize_dont_use_);
		preDef++)
	{
		if (0 == strcmp(pagesizes[preDef].name, name))
			break;
	}

	if ((preDef >= _first_predefined_pagesize_) && (preDef < _last_predefined_pagesize_dont_use_))
		return static_cast<Predefined>(preDef);

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return fp_PageSize::psLetter;
}

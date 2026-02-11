HPDF_3DMeasure_SetName(HPDF_3DMeasure measure,
					   const char* name)
{
	HPDF_STATUS ret = HPDF_OK;
	HPDF_String s;

	s = HPDF_String_New (measure->mmgr, name, 0);
	if (!s)
		return HPDF_Error_GetCode ( s->error);

	ret = HPDF_Dict_Add(measure, "TRL", s);

	return ret;
}

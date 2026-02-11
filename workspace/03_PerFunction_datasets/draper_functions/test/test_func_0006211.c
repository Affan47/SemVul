DataObjectRetrieve(Mushware::tRubyValue inSelf)
{
 	void *pRetVal;
    tRubyValue dataValue = rb_ivar_get(inSelf, MushRubyIntern::AT_embeddedDataPtr());
	Data_Get_Struct(dataValue, void, pRetVal);
	return pRetVal;
}

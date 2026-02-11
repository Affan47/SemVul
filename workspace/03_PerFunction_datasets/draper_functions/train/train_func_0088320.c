getListAttributesVector(UT_GenericVector<const gchar*> * va) const
{


	UT_uint32 count=0,level;
	const gchar * style = NULL;
	const gchar * lid = NULL;
	static gchar  buf[5];

	const PP_AttrProp * pBlockAP = NULL;
	getAP(pBlockAP);
	pBlockAP->getAttribute(PT_STYLE_ATTRIBUTE_NAME,style);
	pBlockAP->getAttribute(static_cast<const gchar *>(PT_LISTID_ATTRIBUTE_NAME),lid);
	if(getAutoNum())
	{
		level = getAutoNum()->getLevel();
	}
	else
	{
		level = 0;
	}
	sprintf(buf,"%i",level);

	if(lid != NULL)
	{
		va->addItem("listid");
		va->addItem(lid);
		count++;
	}
	if(buf != NULL)
	{
		va->addItem("level");
		va->addItem(buf);
		count++;
	}
	if(style != NULL)
	{
		va->addItem(PT_STYLE_ATTRIBUTE_NAME);
		va->addItem(style);
		count++;
	}
	if(count == 0)
	{
		va->addItem( NULL);
	}
}

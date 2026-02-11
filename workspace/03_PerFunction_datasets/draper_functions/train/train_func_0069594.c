explodeStyle(const PD_Document * pDoc, bool bOverwrite)
{
	UT_return_val_if_fail(pDoc,false);


	const gchar * pszStyle = NULL;
	if(getAttribute(PT_STYLE_ATTRIBUTE_NAME, pszStyle))
	{
		PD_Style * pStyle = NULL;

        if(pszStyle && (strcmp(pszStyle, "None") != 0) && pDoc->getStyle(pszStyle,&pStyle))
        {
			UT_Vector vAttrs;
			UT_Vector vProps;

			UT_sint32 i;

			pStyle->getAllAttributes(&vAttrs, 100);
			pStyle->getAllProperties(&vProps, 100);

			for(i = 0; i < vProps.getItemCount(); i += 2)
			{
				const gchar * pName =  (const gchar *)vProps.getNthItem(i);
				const gchar * pValue = (const gchar *)vProps.getNthItem(i+1);
				const gchar * p;

				bool bSet = bOverwrite || !getProperty(pName, p);

				if(bSet)
					setProperty(pName, pValue);
			}


			for(i = 0; i < vAttrs.getItemCount(); i += 2)
			{
				const gchar * pName = (const gchar *)vAttrs.getNthItem(i);
				if(!pName || !strcmp(pName, "type")
				          || !strcmp(pName, "name")
				          || !strcmp(pName, "basedon")
				          || !strcmp(pName, "followedby")
 				          || !strcmp(pName, "props"))
				{
					continue;
				}

				const gchar * pValue = (const gchar *)vAttrs.getNthItem(i+1);
				const gchar * p;

				bool bSet = bOverwrite || !getAttribute(pName, p);

				if(bSet)
					setAttribute(pName, pValue);
			}
		}
	}

	return true;
}

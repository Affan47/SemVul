isFloat(const gchar *t)
{
	guint i;
	for(i=0;i<strlen(t);i++)
		if(!testascii(t[i]) ) return FALSE;
	if(t[0] =='e' || t[0] =='E' ) return FALSE;
	return TRUE;

}

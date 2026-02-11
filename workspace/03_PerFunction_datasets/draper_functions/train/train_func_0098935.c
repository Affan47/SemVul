isvalidusername(struct berval *bv)
{
	int i;
	char *name = bv->bv_val;
	if ((name==NULL)||(name[0]=='\0'))
		return 0;

	if ( ! ( (name[0]>='A' && name[0] <= 'Z') ||
					 (name[0]>='a' && name[0] <= 'z') ||
					 (name[0]>='0' && name[0] <= '9') ||
					 name[0]=='.' || name[0]=='_' ) )
		return 0;

	for (i=1;i<bv->bv_len;i++)
	{
		if ( name[i]=='$' )
		{

			if (name[i+1]!='\0')
				return 0;
		}
		else if ( ! ( (name[i]>='A' && name[i] <= 'Z') ||
									(name[i]>='a' && name[i] <= 'z') ||
									(name[i]>='0' && name[i] <= '9') ||
									name[i]=='.' || name[i]=='_'	|| name[i]=='-') )
			return 0;
	}

	return -1;
}

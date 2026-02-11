parse_avp_name( str *name, int *type, int_str *avp_name)
{
	unsigned int id;
	unsigned int flags;
	char *p;
	char c;
	str s;

	if (name==0 || name->s==0 || name->len==0)
		goto error;

	p = (char*)memchr((void*)name->s, AVP_NAME_DELIM, name->len);
	c = name->s[0];
	if((c!='i' && c!='I' && c!='s' && c!='S') || p==NULL)
	{
		LM_ERR("- use type (s: or i:) in front of avp name\n");
		goto error;
	}

	flags = 0;
	if(p>name->s+1)
	{
		s.s = name->s+1;
		s.len = p - s.s;
		if(str2int(&s, &flags)!=0)
		{
			LM_ERR("bad avp flags\n");
			goto error;
		}
	}
	name->len -= p-name->s+1;
	name->s    = p+1;
	switch (c) {
		case 's': case 'S':
			*type = AVP_NAME_STR;
			avp_name->s = *name;
			break;
		case 'i': case 'I':
			*type = 0;
			if (str2int( name, &id)!=0) {
				LM_ERR("invalid ID <%.*s> not a number\n", name->len, name->s);
				goto error;
			}
			avp_name->n = (int)id;
			break;
		default:
			LM_ERR("unsupported type [%c]\n", c);
			goto error;
	}

	*type |= avp_script_flags(flags);
	return 0;
error:
	return -1;
}

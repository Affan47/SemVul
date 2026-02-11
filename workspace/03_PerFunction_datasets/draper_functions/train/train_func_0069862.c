entry2str_internal_put_value( const char *attrtype, const CSN *attrcsn, CSNType attrcsntype, int attr_state, const Slapi_Value *v, int value_state, char **ecur, char **typebuf, size_t *typebuf_len, int entry2str_ctrl )
{
	const char *type;
	unsigned long options = 0;
        const struct berval *bvp;
	if(entry2str_ctrl & SLAPI_DUMP_STATEINFO)
	{
		char *p;
		size_t attrtypelen= strlen(attrtype);
		size_t attrcsnlen= 0;
		size_t valuecsnlen= 0;
		size_t need= attrtypelen+1;
		if(attrcsn!=NULL)
		{

			attrcsnlen= 1 + csn_string_size();
			need+= attrcsnlen;
		}
		if(v->v_csnset!=NULL)
		{

			valuecsnlen= csnset_string_size(v->v_csnset);
			need+= valuecsnlen;
		}
		if(attr_state==ATTRIBUTE_DELETED)
		{
			need+= DELETED_ATTR_STRSIZE;
		}
		if(value_state==VALUE_DELETED)
		{
			need+= DELETED_VALUE_STRSIZE;
		}
		if(*typebuf_len<need)
		{
			*typebuf= (char*)slapi_ch_realloc(*typebuf,need);
			*typebuf_len= need;
		}
		p= *typebuf;
		type= p;
		strcpy(p,attrtype);
		p+= attrtypelen;
		if(attrcsn!=NULL)
		{
			csn_as_attr_option_string(attrcsntype,attrcsn,p);
			p+= attrcsnlen;
		}
		if(v->v_csnset!=NULL)
		{
			csnset_as_string(v->v_csnset,p);
			p+= valuecsnlen;
		}
		if(attr_state==ATTRIBUTE_DELETED)
		{
			strcpy(p,DELETED_ATTR_STRING);
			p+= DELETED_ATTR_STRSIZE;
		}
		if(value_state==VALUE_DELETED)
		{
			strcpy(p,DELETED_VALUE_STRING);
		}
	}
	else
	{
		type= attrtype;
	}
	bvp = slapi_value_get_berval(v);
	if (entry2str_ctrl & SLAPI_DUMP_NOWRAP)
		options |= LDIF_OPT_NOWRAP;
	if (entry2str_ctrl & SLAPI_DUMP_MINIMAL_ENCODING)
		options |= LDIF_OPT_MINIMAL_ENCODING;
	slapi_ldif_put_type_and_value_with_options( ecur, type, bvp->bv_val, bvp->bv_len, options );
}

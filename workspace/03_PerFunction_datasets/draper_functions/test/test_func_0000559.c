dse_updateNumSubordinates(Slapi_Entry *entry, int op)
{
    int ret= 0;
	int mod_op = 0;
	Slapi_Attr *read_attr = NULL;
	size_t current_sub_count = 0;
	int already_present = 0;


	ret = slapi_entry_attr_find(entry,subordinatecount,&read_attr);
	if (0 == ret)
	{

		Slapi_Value *sval;
		slapi_attr_first_value( read_attr,&sval );
		if (sval!=NULL)
		{
		    const struct berval *bval = slapi_value_get_berval( sval );
		    if (bval!=NULL)
		    {
				already_present = 1;
				current_sub_count = atol(bval->bv_val);
		    }
		}
  	}


	if ( (SLAPI_OPERATION_ADD == op) && !already_present)
	{

		mod_op = LDAP_MOD_ADD;
	}
	else
	{
		if (SLAPI_OPERATION_DELETE == op)
		{
			if (!already_present)
			{

				slapi_log_error( SLAPI_LOG_FATAL, "dse",
						"numsubordinates assertion failure\n" );
				return;
			}
			else
			{
				if (current_sub_count == 1)
				{
					mod_op = LDAP_MOD_DELETE;
				}
				else
				{
					mod_op = LDAP_MOD_REPLACE;
				}
			}
		}
		else
		{
			mod_op = LDAP_MOD_REPLACE;
		}
	}


	if (SLAPI_OPERATION_ADD == op)
	{
		current_sub_count++;
	}
	else
	{
		current_sub_count--;
	}
    {
        char value_buffer[20];
        struct berval *vals[2];
        struct berval val;
        vals[0] = &val;
        vals[1] = NULL;
        sprintf(value_buffer,"%lu",(long unsigned int)current_sub_count);
        val.bv_val = value_buffer;
        val.bv_len = strlen (val.bv_val);
        switch(mod_op)
        {
        case LDAP_MOD_ADD:
            attrlist_merge( &entry->e_attrs, subordinatecount, vals);
            break;
        case LDAP_MOD_REPLACE:
            attrlist_replace( &entry->e_attrs, subordinatecount, vals);
            break;
        case LDAP_MOD_DELETE:
            attrlist_delete( &entry->e_attrs, subordinatecount);
            break;
        }
    }
}

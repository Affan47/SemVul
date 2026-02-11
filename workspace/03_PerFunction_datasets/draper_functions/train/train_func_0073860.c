get_avp_name(struct usr_avp *avp)
{
	void *data;
	switch ( avp->flags&(AVP_NAME_STR|AVP_VAL_STR) )
	{
		case 0:

		case AVP_VAL_STR:

			return 0;
		case AVP_NAME_STR:

			data = (void*)&avp->data;
			return &((struct str_int_data*)data)->name;
		case AVP_NAME_STR|AVP_VAL_STR:

			data = (void*)&avp->data;
			return &((struct str_str_data*)data)->name;
	}

	LM_ERR("unknown avp type (name&val) %d\n",
		avp->flags&(AVP_NAME_STR|AVP_VAL_STR));
	return 0;
}

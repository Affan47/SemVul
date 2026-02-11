icalvalue_free (icalvalue* v)
{
    icalerror_check_arg_rv((v != 0),"value");

#ifdef ICAL_FREE_ON_LIST_IS_ERROR
    icalerror_assert( (v->parent ==0),"This value is still attached to a property");

#else
    if(v->parent !=0){
	return;
    }
#endif

    if(v->x_value != 0){
        free(v->x_value);
    }

    switch (v->kind){
	case ICAL_BINARY_VALUE:
	case ICAL_ATTACH_VALUE: {
	    if (v->data.v_attach) {
		icalattach_unref (v->data.v_attach);
		v->data.v_attach = NULL;
	    }

	    break;
	}
	case ICAL_TEXT_VALUE:
	case ICAL_CALADDRESS_VALUE:
	case ICAL_URI_VALUE:
	case ICAL_QUERY_VALUE:
	{
	    if (v->data.v_string != 0) {
		free((void*)v->data.v_string);
		v->data.v_string = 0;
	    }
	    break;
	}
	case ICAL_RECUR_VALUE:
	{
	    if(v->data.v_recur != 0){
		free((void*)v->data.v_recur);
		v->data.v_recur = 0;
	    }
	    break;
	}

	default:
	{

	}
    }

    v->kind = ICAL_NO_VALUE;
    v->size = 0;
    v->parent = 0;
    memset(&(v->data),0,sizeof(v->data));
    v->id[0] = 'X';
    free(v);
}

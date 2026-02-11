xmmsv_free (xmmsv_t *val)
{
	x_return_if_fail (val);

	switch (val->type) {
		case XMMSV_TYPE_NONE :
		case XMMSV_TYPE_END :
		case XMMSV_TYPE_INT32 :
			break;
		case XMMSV_TYPE_ERROR :
			free (val->value.error);
			val->value.error = NULL;
			break;
		case XMMSV_TYPE_STRING :
			free (val->value.string);
			val->value.string = NULL;
			break;
		case XMMSV_TYPE_COLL:
			xmmsv_coll_unref (val->value.coll);
			val->value.coll = NULL;
			break;
		case XMMSV_TYPE_BIN :
			free (val->value.bin.data);
			val->value.bin.len = 0;
			break;
		case XMMSV_TYPE_LIST:
			xmmsv_list_free (val->value.list);
			val->value.list = NULL;
			break;
		case XMMSV_TYPE_DICT:
			xmmsv_dict_free (val->value.dict);
			val->value.dict = NULL;
			break;
		case XMMSV_TYPE_BITBUFFER:
			if (!val->value.bit.ro && val->value.bit.buf) {
				free (val->value.bit.buf);
			}
			val->value.bit.buf = NULL;
			break;
	}

	free (val);
}

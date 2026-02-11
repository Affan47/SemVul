getvalue(SANE_Handle handle, SANE_Int option, void *value)
{
	KodakAio_Scanner *s = (KodakAio_Scanner *) handle;
	SANE_Option_Descriptor *sopt = &(s->opt[option]);
	Option_Value *sval = &(s->val[option]);

	DBG(17, "%s: option = %d\n", __func__, option);

	switch (option) {

	case OPT_NUM_OPTS:
	case OPT_BIT_DEPTH:

	case OPT_RESOLUTION:
	case OPT_PREVIEW:
	case OPT_TL_X:
	case OPT_TL_Y:
	case OPT_BR_X:
	case OPT_BR_Y:
		*((SANE_Word *) value) = sval->w;
		break;

	case OPT_MODE:
	case OPT_SOURCE:
	case OPT_ADF_MODE:
		strcpy((char *) value, sopt->constraint.string_list[sval->w]);
		break;
	case OPT_PADDING:
		*((SANE_Bool *) value) = sval->w;
		break;

	default:
		return SANE_STATUS_INVAL;
	}

	return SANE_STATUS_GOOD;
}

c_meth2str(struct sample *smp)
{
	int len;
	enum http_meth_t meth;

	if (smp->data.meth.meth == HTTP_METH_OTHER) {

		len = smp->data.meth.str.len;
		smp->data.str.str = smp->data.meth.str.str;
		smp->data.str.len = len;
		smp->type = SMP_T_STR;
	}
	else if (smp->data.meth.meth < HTTP_METH_OTHER) {

		meth = smp->data.meth.meth;
		smp->data.str.str = http_known_methods[meth].name;
		smp->data.str.len = http_known_methods[meth].len;
		smp->flags |= SMP_F_CONST;
		smp->type = SMP_T_STR;
	}
	else {

		return 0;
	}
	return 1;
}

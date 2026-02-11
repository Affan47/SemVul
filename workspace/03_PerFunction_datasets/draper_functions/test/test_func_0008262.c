getvar_s(var *v)
{

	if ((v->type & (VF_NUMBER | VF_CACHED)) == VF_NUMBER) {
		fmt_num(g_buf, MAXVARFMT, getvar_s(intvar[CONVFMT]), v->number, TRUE);
		v->string = xstrdup(g_buf);
		v->type |= VF_CACHED;
	}
	return (v->string == NULL) ? "" : v->string;
}

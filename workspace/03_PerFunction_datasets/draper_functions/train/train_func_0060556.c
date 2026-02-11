EXP_Grace(const struct sess *sp, const struct object *o)
{
	double r;

	r = (double)cache_param->default_grace;
	if (o->exp.grace >= 0.)
		r = o->exp.grace;
	if (sp != NULL && sp->exp.grace > 0. && sp->exp.grace < r)
		r = sp->exp.grace;
	return (EXP_Ttl(sp, o) + r);
}

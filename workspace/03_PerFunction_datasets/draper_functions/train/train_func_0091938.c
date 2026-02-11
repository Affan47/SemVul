cfind(struct vars * v,
	  struct cnfa * cnfa,
	  struct colormap * cm)
{
	struct dfa *s;
	struct dfa *d;
	chr		   *cold;
	int			ret;

	s = newdfa(v, &v->g->search, cm, &v->dfa1);
	NOERR();
	d = newdfa(v, cnfa, cm, &v->dfa2);
	if (ISERR())
	{
		assert(d == NULL);
		freedfa(s);
		return v->err;
	}

	ret = cfindloop(v, cnfa, cm, d, s, &cold);

	freedfa(d);
	freedfa(s);
	NOERR();
	if (v->g->cflags & REG_EXPECT)
	{
		assert(v->details != NULL);
		if (cold != NULL)
			v->details->rm_extend.rm_so = OFF(cold);
		else
			v->details->rm_extend.rm_so = OFF(v->stop);
		v->details->rm_extend.rm_eo = OFF(v->stop);
	}
	return ret;
}

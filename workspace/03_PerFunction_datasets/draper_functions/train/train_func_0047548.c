player_generate(struct player *p, const player_sex *s,
		const struct player_race *r, const struct player_class *c)
{
	if (!s) s = &sex_info[p->psex];
	if (!c)
		c = p->class;
	if (!r)
		r = p->race;

	p->sex = s;
	p->class = c;
	p->race = r;


	p->max_lev = p->lev = 1;


	p->expfact = p->race->r_exp + p->class->c_exp;


	p->hitdie = p->race->r_mhp + p->class->c_mhp;


	p->mhp = p->hitdie;


	p->player_hp[0] = p->hitdie;


	get_ahw(p);

	p->history = get_history(p->race->history, &p->sc);
	p->sc_birth = p->sc;
}

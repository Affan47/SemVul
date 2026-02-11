GetExp(int skill)
{
	forlist(this) {
		Skill *s = (Skill *) elem;
		if (s->type == skill) {
			return s->exp;
		}
	}
	return 0;
}

add_phrases(phrases_t *s, phrase_t *t)
{
	if(!t)
		return s;
	if(!s)
		s = xmalloc(sizeof(*s));
	if(t)
	{
		s->phrases = xrealloc(s->phrases, (s->nphrases + 1) * sizeof(s->phrases[0]));
		s->phrases[s->nphrases] = t;
		s->nphrases++;
	}
	return s;
}

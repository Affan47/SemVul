SuffRebuildGraph(const GNode *transform, Suff *s)
{
	char	*cp;
	Suff	*s2 = NULL;


	if (strncmp(transform->name, s->name, strlen(s->name)) == 0) {
		cp = transform->name + strlen(s->name);

		if (cp[0] == '\0')
			s2 = suffNull;
		else
			s2 = SuffSuffFind(cp);
		if (s2 != NULL) {


			SuffInsert(&s2->children, s);
			SuffInsert(&s->parents, s2);
			return;
		}
	}


	cp = SuffSuffIsSuffix(s, transform->name);
	if (cp != NULL) {


		cp[1] = '\0';
		s2 = SuffSuffFind(transform->name);


		cp[1] = s->name[0];
		if (s2 != NULL) {


			SuffInsert(&s->children, s2);
			SuffInsert(&s2->parents, s);
		}
	}
}

pset_union(s1, s2, dontreplicate)
Pset s1, s2;
int dontreplicate;
{
	Pset hd, curr, new = NULL;
	Pset replicas2 = NULL, temps2 = s2;


	if (dontreplicate) replicas2 = s2;
	else while (temps2 != NULL) {
		new_node(Pset, new, new);
		if (new == NULL) return NULL;
		new->posnum = temps2->posnum;
		if (replicas2 == NULL) replicas2 = new;
		else curr->nextpos = new;
		curr = new;
		temps2 = temps2->nextpos;
	}

	hd = NULL;
	curr = NULL;
	while (s1 != NULL) {
		if (!occurs_in(s1->posnum, s2)) {
			new_node(Pset, new, new);
			if (new == NULL) return NULL;
			new->posnum = s1->posnum;
			if (hd == NULL) hd = new;
			else curr->nextpos = new;
		}
		curr = new;
		s1 = s1->nextpos;
	}
	if (hd == NULL) hd = replicas2;
	else curr->nextpos = replicas2;
	return hd;
}

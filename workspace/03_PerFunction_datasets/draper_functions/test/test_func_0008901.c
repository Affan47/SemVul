parent_dlevel(s, pd)
	const char	*s;
	struct proto_dungeon *pd;
{
	int i, j, num, base, dnum = parent_dnum(s, pd);
	branch *curr;


	i = find_branch(s, pd);
	num = level_range(dnum, pd->tmpbranch[i].lev.base,
					      pd->tmpbranch[i].lev.rand,
					      pd->tmpbranch[i].chain,
					      pd, &base);


	i = j = rn2(num);
	do {
		if (++i >= num) i = 0;
		for (curr = branches; curr; curr = curr->next)
			if ((curr->end1.dnum == dnum && curr->end1.dlevel == base+i) ||
				(curr->end2.dnum == dnum && curr->end2.dlevel == base+i))
				break;
	} while (curr && i != j);
	return (base + i);
}

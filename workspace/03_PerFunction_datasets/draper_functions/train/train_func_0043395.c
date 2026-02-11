sortDomainUsersTotal(char *domain)
{
	int tmpnval, i, j, max, tmp;
	struct domain *domainptr;
	struct user *sym;
	struct user *tmp1, *tmp2;

	tmpnval = -1;
	for (i = 0; i < DomainsTab.nval; i++)
		if (strcasecmp(DomainsTab.alldomains[i].domain, domain) == 0) {
			tmpnval = i;
			break;
		}
	domainptr = (struct domain *)&DomainsTab.alldomains[i];

	for (i = 0; i < MAXUSERS; i++) {
		for (sym = domainptr->users[i]; sym != NULL; sym = sym->next)
			addUserToSortTab(sym);
	}

	for (i = 0; i < SortDomain.nval; i++) {
		max = i;
		for (j = i+1; j <= SortDomain.nval - 1; j++) {
			tmp1 = (user *)(SortDomain.allusers[j]);
			tmp2 = (user *)(SortDomain.allusers[max]);
			if (tmp1 != NULL && tmp2 != NULL)
				if ((tmp1->from_cnt + tmp1->to_cnt) > (tmp2->from_cnt + tmp2->to_cnt))
					max = j;
		}
		tmp = SortDomain.allusers[i];
		SortDomain.allusers[i] = SortDomain.allusers[max];
		SortDomain.allusers[max] = tmp;
	}
}

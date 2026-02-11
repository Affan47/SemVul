expand_faci(list_t *restrict rlist, list_t *restrict head, int *restrict deep)
{
	repl_t * rent = getrepl(rlist);
	list_t * tmp, * safe, * ptr = (list_t*)0;

	list_for_each(tmp, sysfaci_start) {
	    if (!strcmp(getfaci(tmp)->name, rent->r[0].name)) {
		ptr = &getfaci(tmp)->replace;
		break;
	    }
	}

	if (!ptr || list_empty(ptr)) {
	    delete(rlist);
	    if (--(*rent->r[0].ref) <= 0)
		free(rent->r[0].ref);
	    free(rent);
	    goto out;
	}

	list_for_each_safe(tmp, safe, ptr) {
	    repl_t * rnxt = getrepl(tmp);
	    if (rnxt->flags & 0x0001) {
		error("Loop detected during expanding system facilities in the insserv.conf file(s): %s\n",
		      rnxt->r[0].name);
	    }
	    if (*rnxt->r[0].name == '$') {
		if (*deep > 10) {
		    warn("The nested level of the system facilities in the insserv.conf file(s) is to large\n");
		    goto out;
		}
		(*deep)++;
		rnxt->flags |= 0x0001;
		expand_faci(tmp, head, deep);
		rnxt->flags &= ~0x0001;
		(*deep)--;
	    } else if (*deep > 0) {
		repl_t *restrict subst;
		if (posix_memalign((void*)&subst, sizeof(void*), alignof(repl_t)) != 0)
		    error("%s", strerror(errno));
		insert(&subst->r_list, head->prev);
		subst->r[0] = rnxt->r[0];
		(*subst->r[0].ref) = 1;
	    }
	}
out:
	return;
}

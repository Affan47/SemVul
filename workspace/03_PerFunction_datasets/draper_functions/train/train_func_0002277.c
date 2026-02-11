sched(void)
{
	char *flags;
	Job *j;
	Bufblock *buf;
	int slot;
	Node *n;
	Envy *e;

	if(jobs == 0){
		usage();
		return;
	}
	j = jobs;
	jobs = j->next;
	if(DEBUG(D_EXEC))
		fprint(1, "firing up job for target %s\n", wtos(j->t, ' '));
	slot = nextslot();
	events[slot].job = j;
	buf = newbuf();
	e = buildenv(j, slot);
	shprint(j->r->recipe, e, buf, j->r->shellt);
	if(!tflag && (nflag || !(j->r->attr&QUIET)))
		Bwrite(&bout, buf->start, (long)strlen(buf->start));
	freebuf(buf);
	if(nflag||tflag){
		for(n = j->n; n; n = n->next){
			if(tflag){
				if(!(n->flags&VIRTUAL))
					touch(n->name);
				else if(explain)
					Bprint(&bout, "no touch of virtual '%s'\n", n->name);
			}
			n->time = time((long *)0);
			MADESET(n, MADE);
		}
	} else {
		if(DEBUG(D_EXEC))
			fprint(1, "recipe='%s'", j->r->recipe);
		Bflush(&bout);
		if(j->r->attr&NOMINUSE)
			flags = 0;
		else
			flags = "-e";
		events[slot].pid = execsh(flags, j->r->recipe, 0, e, j->r->shellt, j->r->shellcmd);
		usage();
		nrunning++;
		if(DEBUG(D_EXEC))
			fprint(1, "pid for target %s = %d\n", wtos(j->t, ' '), events[slot].pid);
	}
}

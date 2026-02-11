wunlock(RWLock *l)
{
	Task *t;

	if(l->writer == nil){
		fprint(2, "wunlock: not locked\n");
		abort();
	}
	l->writer = nil;
	if(l->readers != 0){
		fprint(2, "wunlock: readers\n");
		abort();
	}
	while((t = l->rwaiting.head) != nil){
		deltask(&l->rwaiting, t);
		l->readers++;
		taskready(t);
	}
	if(l->readers == 0 && (t = l->wwaiting.head) != nil){
		deltask(&l->wwaiting, t);
		l->writer = t;
		taskready(t);
	}
}

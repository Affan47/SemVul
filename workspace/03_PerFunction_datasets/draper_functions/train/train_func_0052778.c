arrange(Monitor *m) {
	if(m)
		showhide(m->stack);
	else for(m = mons; m; m = m->next)
		showhide(m->stack);
	if(m)
		arrangemon(m);
	else for(m = mons; m; m = m->next)
		arrangemon(m);
}

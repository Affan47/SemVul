get_highlight_state(BW *w,int line)
{
	P *tmp = 0;
	int state;


	int y = line-w->top->line+w->y;

	if(!w->o.highlight || !w->o.syntax)
		return -1;


	if (w->parent->t->t->syntab[y]>=0)
		return w->parent->t->t->syntab[y];


	while (y > w->y && w->parent->t->t->syntab[y] < 0) --y;


	if (w->parent->t->t->syntab[y]<0) {

		state = 0;
		tmp = pdup(w->top);
		if(w->o.syntax->sync_lines >= 0 && tmp->line > w->o.syntax->sync_lines)
			pline(tmp, tmp->line-w->o.syntax->sync_lines);
		else
			p_goto_bof(tmp);
		while(tmp->line!=y-w->y+w->top->line)
			state = parse(w->o.syntax,tmp,state);
		w->parent->t->t->syntab[y] = state;
		w->parent->t->t->updtab[y] = 1;
		prm(tmp);
	}


	tmp = pdup(w->top);
	pline(tmp, y-w->y+w->top->line);
	state = w->parent->t->t->syntab[y];
	while(tmp->line!=w->top->line+w->h-1 && !piseof(tmp)) {
		state = parse(w->o.syntax,tmp,state);
		w->parent->t->t->syntab[++y] = state;
		w->parent->t->t->updtab[y] = 1;
		}
	prm(tmp);
	while(y<w->y+w->h-1) {
		w->parent->t->t->syntab[++y] = state;
		}


	y = line - w->top->line + w->y;
	return w->parent->t->t->syntab[y];
}

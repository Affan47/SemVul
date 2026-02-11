urindent(BW *bw)
{
	if (square) {
		if (markb && markk && markb->b == markk->b && markb->byte <= markk->byte && markb->xcol <= markk->xcol) {
			P *p = pdup(markb);

			do {
				pcol(p, markb->xcol);
				pfill(p, markb->xcol + bw->o.istep, bw->o.indentc);
			} while (pnextl(p) && p->line <= markk->line);
			prm(p);
		}
	} else {
		if (!markb || !markk || markb->b != markk->b || bw->cursor->byte < markb->byte || bw->cursor->byte > markk->byte || markb->byte == markk->byte) {
			setindent(bw);
		} else if ( 1 ) {
			P *p = pdup(markb);
			P *q = pdup(markb);
			int indwid;

			if (bw->o.indentc=='\t')
				indwid = bw->o.tab * bw->o.istep;
			else
				indwid = bw->o.istep;

			while (p->byte < markk->byte) {
				p_goto_bol(p);
				if (!piseol(p)) {
					int col;
					pset(q, p);
					p_goto_indent(q, bw->o.indentc);
					col = piscol(q);
					bdel(p,q);
					pfill(p,col+indwid,bw->o.indentc);
				}
				pnextl(p);
			}
			prm(p);
			prm(q);
		} else if (purity_check(bw->o.indentc,0)) {
			P *p = pdup(markb);

			while (p->byte < markk->byte) {
				p_goto_bol(p);
				if (!piseol(p))
					while (piscol(p) < bw->o.istep) {
						binsc(p, bw->o.indentc);
						pgetc(p);
					}
				pnextl(p);
			}
			prm(p);
		} else {

			msgnw(bw->parent,US "Selected lines not properly indented");
			return 1;
		}
	}
	return 0;
}

upgdn(BW *bw)
{
	if (menu_above) {
		if (bw->parent->link.prev->watom==&watommenu) {
			return umpgdn(bw->parent->link.prev->object);
		}
	} else {
		if (bw->parent->link.next->watom==&watommenu) {
			return umpgdn(bw->parent->link.next->object);
		}
	}
	bw = (BW *) bw->parent->main->object;
	if (bw->o.hex ? bw->cursor->byte/16 == bw->b->eof->byte/16 : bw->cursor->line == bw->b->eof->line)
		return -1;
	if (pgamnt < 0)
		scrdn(bw, bw->h / 2 + bw->h % 2, 1);
	else if (pgamnt < bw->h)
		scrdn(bw, bw->h - pgamnt, 1);
	else
		scrdn(bw, 1, 1);
	return 0;
}

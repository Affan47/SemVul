udnslide(BW *bw)
{
	bw = (BW *) bw->parent->main->object;
	if (bw->o.hex ? bw->top->line/16 + bw->h <= bw->top->b->eof->byte/16 : bw->top->line + bw->h <= bw->top->b->eof->line) {
		if (bw->o.hex ? bw->top->byte/16 != bw->cursor->byte/16 : bw->top->line != bw->cursor->line)
			uuparw(bw);
		scrdn(bw, 1, 0);
		return 0;
	} else

		return udnarw(bw);
}

idxUpDown(Cursor & cur, bool up) const
{
	idx_type target = up;
	if (cur.idx() == target)
		return false;
	cur.idx() = target;
	cur.pos() = cur.cell().x2pos(&cur.bv(), cur.x_target());
	return true;
}

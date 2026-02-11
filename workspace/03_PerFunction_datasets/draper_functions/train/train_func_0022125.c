node_correct_position_end (JSNode *self, int end)
{
	if (!self->pn_pos.begin)
		self->pn_pos.begin = end;
	if (self->pn_pos.end < end)
		self->pn_pos.end = end;
}

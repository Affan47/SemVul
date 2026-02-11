goto_rec(int pos)
{
	if (ds_state == dsSelect)
	{
		return seek(pos - 1);
	}
	return false;
}

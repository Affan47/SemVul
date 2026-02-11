RemoveRow(unsigned rowId)
{
	Row *out;
	if (rows.Delete(rowId, out))
	{
		DeleteRow(out);
		return true;
	}
	return false;
}

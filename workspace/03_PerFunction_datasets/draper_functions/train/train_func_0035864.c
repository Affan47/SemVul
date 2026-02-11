extract(std::size_t pos, float& val)
{
	if (isNull(pos))
		return false;
	val = static_cast<float>(sqlite3_column_double(_pStmt, (int) pos));
	return true;
}

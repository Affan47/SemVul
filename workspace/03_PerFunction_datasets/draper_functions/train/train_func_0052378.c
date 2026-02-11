extract(std::size_t pos, Poco::Data::BLOB& val)
{
	if (isNull(pos))
		return false;
	int size = sqlite3_column_bytes(_pStmt, (int) pos);
	const char* pTmp = reinterpret_cast<const char*>(sqlite3_column_blob(_pStmt, (int) pos));
	val = Poco::Data::BLOB(pTmp, size);
	return true;
}

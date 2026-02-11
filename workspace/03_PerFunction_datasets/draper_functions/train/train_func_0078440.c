to_local8bit(docstring const & s)
{

	if (s.empty())
		return string();
	QByteArray const local = toqstr(s).toLocal8Bit();
	if (local.size() == 0)
		throw to_local8bit_failure();
	return string(local.begin(), local.end());
}

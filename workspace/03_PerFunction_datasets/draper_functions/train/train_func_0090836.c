boolQuestion(const QString& line)
{
	ts_boolanswer ret = KGpgSignTransactionHelper::boolQuestion(line);

	if (ret == BA_UNKNOWN)
		ret = KGpgTransaction::boolQuestion(line);

	return ret;
}

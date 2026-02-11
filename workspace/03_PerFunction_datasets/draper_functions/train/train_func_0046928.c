getsrvinfo (const char *rrname,
            srvinfo **res)
{
	unsigned char *answer;
	int length;
	int ret;

	ret = perform_query (rrname, &answer, &length);
	if (ret != 0)
		return ret;

	ret = parse_answer (answer, length, res);
	free (answer);

	return ret;
}

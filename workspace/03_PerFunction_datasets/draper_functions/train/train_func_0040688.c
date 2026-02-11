saveMessageContents(string s)
{
	if (t && !ferror(t))
		if (fwrite(s.c_str(), s.size(), 1, t) != 1)
			;

	bytesDone += s.size();

	cb.reportProgress(bytesDone, 0, 0, 1);
}

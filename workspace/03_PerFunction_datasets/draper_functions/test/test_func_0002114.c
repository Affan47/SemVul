ConvertFromCML (char const *cml, GsfOutput *output, const char *mime_type, const char *options)
{
	int sock = OpenBabelSocket ();
	if (sock <= 0)
		return;
	std::ostringstream os;
	size_t l = strlen (cml);
	os << "-i cml -o ";
	os << MimeToBabelType (mime_type);
	if (options)
		os << " " << options;
	os << " -l " << l << " -D";
	write (sock, os.str ().c_str (), os.str ().length ());
	write (sock, cml, l);
	time_t timeout = time (NULL) + 60;
	char inbuf[256], *start = inbuf, *end;
	int cur, index = 0, length = 0;
	while (time (NULL) < timeout) {
		if ((cur = read (sock, start + index, ((length)? length: 255) - index)) > 0) {
			index += cur;
			start[index] = 0;
			if (start == inbuf) {
				if ((end = strchr (inbuf, ' '))) {
					length = strtoul (inbuf, NULL, 10);
					start = reinterpret_cast <char *> (g_malloc (length + 1));
					if (!start)
						break;
					strcpy (start, end + 1);
					index = strlen (start);
				}
			}
			if (index == length) {
				gsf_output_write (output, length, reinterpret_cast <guint8 *> (start));
				break;
			}
		} else
			break;
	}
}

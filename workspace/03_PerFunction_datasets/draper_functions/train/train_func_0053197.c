load(const HTTPRequest& request)
{
	NullPartHandler nah;
	NullInputStream nis;
	load(request, nis, nah);
}

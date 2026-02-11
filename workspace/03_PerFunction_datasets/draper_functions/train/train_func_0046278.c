on_update_progress()
{
	progress_bar->pulse();

	if (-1 == outfile)
		outfile = open(outfilename.c_str(), O_RDONLY);
	if (-1 == outfile)
		return true;

	struct stat stat;
	EC_THROW(-1 == fstat(outfile, &stat));
	off_t size = stat.st_size/(1024);
	char buf[512];
	int len;
	if(size<1024)
	{
		len = snprintf(buf, 512, _("Recording %s To %s (%u Kb)"),channelname.c_str(), outfilename.c_str(), (unsigned int)size);
	}
	else{
		off_t mb=size/1024;
		off_t kb=size%1024;
		len = snprintf(buf, 512, _("Recording %s To %s (%u.%u Mb)"),channelname.c_str(), outfilename.c_str(), (unsigned int)mb,(unsigned int)kb);
	}
	buf[len] = 0;

	record_name->set_label(buf);
	return true;
}

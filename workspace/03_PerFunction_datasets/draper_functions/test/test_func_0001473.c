gbs_printinfo(struct gbs *gbs, long verbose)
{
	printf(_("GBSVersion:     %ld\n"
	         "Title:          \"%s\"\n"
	         "Author:         \"%s\"\n"
	         "Copyright:      \"%s\"\n"
	         "Load address:   0x%04x\n"
	         "Init address:   0x%04x\n"
	         "Play address:   0x%04x\n"
	         "Stack pointer:  0x%04x\n"
	         "File size:      0x%08x\n"
	         "ROM size:       0x%08lx (%ld banks)\n"
	         "Subsongs:       %ld\n"),
	       gbs->version,
	       gbs->title,
	       gbs->author,
	       gbs->copyright,
	       gbs->load,
	       gbs->init,
	       gbs->play,
	       gbs->stack,
	       (unsigned int)gbs->filesize,
	       gbs->romsize,
	       gbs->romsize/0x4000,
	       gbs->songs);
	if (gbs->version == 2) {
		printf(_("CRC32:		0x%08lx/0x%08lx (%s)\n"),
		       (unsigned long)gbs->crc, (unsigned long)gbs->crcnow,
		       gbs->crc == gbs->crcnow ? _("OK") : _("Failed"));
	}
	if (verbose && gbs->version == 2) {
		long i;
		for (i=0; i<gbs->songs; i++) {
			printf(_("Subsong %03ld:	"), i);
			if (gbs->subsong_info[i].title) {
				printf("\"%s\" ", gbs->subsong_info[i].title);
			} else {
				printf("%s ", _("untitled"));
			}
			if (gbs->subsong_info[i].len) {
				printf(_("(%ld seconds)\n"),
				       (long)(gbs->subsong_info[i].len >> GBS_LEN_SHIFT));
			} else {
				printf("%s\n", _("no time limit"));
			}
		}
	}
}

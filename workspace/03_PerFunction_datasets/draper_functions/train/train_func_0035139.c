asc_prt_adv_bios(struct seq_file *m, struct Scsi_Host *shost)
{
	struct asc_board *boardp = shost_priv(shost);
	ushort major, minor, letter;

	seq_puts(m, "\nROM BIOS Version: ");


	if (boardp->bios_signature != 0x55AA) {
		seq_puts(m, "Disabled or Pre-3.1\n"
			"BIOS either disabled or Pre-3.1. If it is pre-3.1, then a newer version\n"
			"can be found at the ConnectCom FTP site: ftp://ftp.connectcom.net/pub\n");
	} else {
		major = (boardp->bios_version >> 12) & 0xF;
		minor = (boardp->bios_version >> 8) & 0xF;
		letter = (boardp->bios_version & 0xFF);

		seq_printf(m, "%d.%d%c\n",
				   major, minor,
				   letter >= 26 ? '?' : letter + 'A');


		if (major < 3 || (major <= 3 && minor < 1) ||
		    (major <= 3 && minor <= 1 && letter < ('I' - 'A'))) {
			seq_puts(m, "Newer version of ROM BIOS is available at the ConnectCom FTP site:\n"
				"ftp://ftp.connectcom.net/pub\n");
		}
	}
}

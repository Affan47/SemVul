trans2_qfsinfo(const u_char *param, const u_char *data, int pcnt, int dcnt)
{
    static int level = 0;
    const char *fmt="";

    if (request) {
	TCHECK2(*param, 2);
	level = EXTRACT_LE_16BITS(param);
	fmt = "InfoLevel=[d]\n";
	smb_fdata(param, fmt, param + pcnt, unicodestr);
    } else {
	switch (level) {
	case 1:
	    fmt = "idFileSystem=[W]\nSectorUnit=[D]\nUnit=[D]\nAvail=[D]\nSectorSize=[d]\n";
	    break;
	case 2:
	    fmt = "CreationTime=[T2]VolNameLength=[lb]\nVolumeLabel=[c]\n";
	    break;
	case 0x105:
	    fmt = "Capabilities=[W]\nMaxFileLen=[D]\nVolNameLen=[lD]\nVolume=[C]\n";
	    break;
	default:
	    fmt = "UnknownLevel\n";
	    break;
	}
	smb_fdata(data, fmt, data + dcnt, unicodestr);
    }
    if (dcnt) {
	printf("data:\n");
	print_data(data, dcnt);
    }
    return;
trunc:
    printf("[|SMB]");
    return;
}

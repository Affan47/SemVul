scsiProbeNew(int* num_ami_devices, int* sg_nos)
{
	int inplen = *num_ami_devices;
	int numdevfound = 0;
	char linebuf[81];
	char vendor[81];
	int lineno = 0;
	FILE* fp;

	fp = fopen("/proc/scsi/sg/device_strs","r");
	if(fp == NULL) {

		return 1;
	}

	while(1) {

		if(fgets(linebuf, 80, fp) == NULL) {
			break;
		}

		if(sscanf(linebuf, "%s", vendor) == 1) {
			if(strncmp(vendor, "AMI", strlen("AMI")) == 0)
			{
				numdevfound++;
				sg_nos[numdevfound-1] = lineno;
				if(numdevfound == inplen) {
					break;
				}
			}
			lineno++;
		}
	}

	*num_ami_devices = numdevfound;
	fclose(fp);

	return 0;
}

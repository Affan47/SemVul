dl_srecord(FILE *in)
{
	char buffer[128];
	long base_offset=0;
	int s123_count=0;

	printf("Downloading S-Record...\n");
	while(!feof(in)) {
		unsigned int count, address;
		char checksum;
		char data[128];
		int x;

		fgets(buffer, 127, in);
		if(buffer[0] != 'S') continue;

		count = decode_line(buffer, &address, &data[0], &checksum);

		switch(buffer[1]) {
		case '0':


			break;
		case '1': case '2': case '3':

			for(x=0;x<count;x++) {
				Memory_StorByte(x + address + base_offset,
							data[x] & 0x000000FF);
			}
			s123_count++;
			break;
		case '5':

			if(address != s123_count) {
				printf("S5 record says there should have been %d S[123] lines, but there have only been %d.\n",
						address, s123_count);
			}
			break;
		case '7': case '8': case '9':


			memory_core.pc = address;

			Memory_Stor(32,memory_core.a[7]+4,memory_core.pc);
			break;
		}
	}
	printf("Done downloading S-Record.\n");

}

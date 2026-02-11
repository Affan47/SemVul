analyze_reply(RawRequest_t *raw_cmd, int do_print)
{
	int ret, bytes, newbytes;

	bytes = 0;
	while(1) {
		ret = analyze_one_reply(raw_cmd, &newbytes, do_print);
		bytes += newbytes;
		switch(ret) {
			case 0:
				return bytes;
			case 1:
				raw_cmd++;
				break;
			case -1:
				if(bytes)
					return bytes;
				else
					return 0;
		}
	}
}

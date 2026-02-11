testcompval(int rv, char *func)
{
	switch (rv)
	{
	   case Z_OK:
	   case Z_STREAM_END:
	   case Z_NEED_DICT:
		break;

	   case Z_MEM_ERROR:
		fprintf(stderr, "atop/atopsar - "
		        "%s: failed due to lack of memory\n", func);
		cleanstop(7);

	   case Z_BUF_ERROR:
		fprintf(stderr, "atop/atopsar - "
			"%s: failed due to lack of room in buffer\n", func);
		cleanstop(7);

   	   case Z_DATA_ERROR:
		fprintf(stderr, "atop/atopsar - "
		        "%s: failed due to corrupted/incomplete data\n", func);
		cleanstop(7);

	   default:
		fprintf(stderr, "atop/atopsar - "
		        "%s: unexpected error %d\n", func, rv);
		cleanstop(7);
	}
}

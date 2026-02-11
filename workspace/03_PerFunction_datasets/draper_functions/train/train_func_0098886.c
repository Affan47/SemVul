swapn4b(void *dst, const void *src, size_t nn)
{
	char *op = dst;
	const char *ip = src;


	while(nn > 3)
	{
		op[0] = ip[3];
		op[1] = ip[2];
		op[2] = ip[1];
		op[3] = ip[0];
		op[4] = ip[7];
		op[5] = ip[6];
		op[6] = ip[5];
		op[7] = ip[4];
		op[8] = ip[11];
		op[9] = ip[10];
		op[10] = ip[9];
		op[11] = ip[8];
		op[12] = ip[15];
		op[13] = ip[14];
		op[14] = ip[13];
		op[15] = ip[12];
		op += 16;
		ip += 16;
		nn -= 4;
	}
	while(nn-- != 0)
	{
		op[0] = ip[3];
		op[1] = ip[2];
		op[2] = ip[1];
		op[3] = ip[0];
		op += 4;
		ip += 4;
	}
}

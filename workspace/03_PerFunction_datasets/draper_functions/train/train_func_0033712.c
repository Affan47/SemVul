do_checksum(unsigned char *x)
{
    printf("Checksum: 0x%hx", x[0x7f]);
    {
	unsigned char sum = 0;
	int i;
	for (i = 0; i < 128; i++)
	    sum += x[i];
	if (sum) {
	    printf(" (should be 0x%hx)", (unsigned char)(x[0x7f] - sum));
	    has_valid_checksum = 0;
	}
    }
    printf("\n");
}

dump_hex(FILE *file, const u8 *data, int len, int offset)
{
	int i;

	fprintf(file, "Offset\t\tValues\n");
	fprintf(file, "------\t\t------");
	for (i = 0; i < len; i++) {
		if (i % 16 == 0)
			fprintf(file, "\n0x%04x:\t\t", i + offset);
		fprintf(file, "%02x ", data[i]);
	}
	fprintf(file, "\n");
}

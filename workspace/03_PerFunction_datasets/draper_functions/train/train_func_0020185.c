save_state(FILE *file)
{
	unsigned int pos;

	fprintf(file, "%u\n2\n%u\n", rec_entry, rec_length + 1);
	for (pos = 0; pos <= rec_length; pos++)
		fprintf(file, "%u\n", (unsigned int)rec_numbers[pos]);
}

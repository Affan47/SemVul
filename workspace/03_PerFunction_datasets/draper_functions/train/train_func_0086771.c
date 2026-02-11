init_array(unsigned long standard_MFM_2_bit_cell_size, int nb_of_bits)
{
	int i;

	for (i = 0; i < FDI_MAX_ARRAY; i++) {
		psarray[i].size = standard_MFM_2_bit_cell_size;
		total += psarray[i].size;
		psarray[i].number_of_bits = nb_of_bits;
		totaldiv += psarray[i].number_of_bits;
	}
	array_index = 0;
}

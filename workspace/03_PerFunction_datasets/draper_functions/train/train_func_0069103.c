ssd_put_index(int slave, int index)
{
	unsigned long *index_bits = ssd_index_bits;

	if (slave) {
		index_bits = ssd_index_bits_sl;
	}

	if (test_and_clear_bit(index,  index_bits)) {
		atomic_dec(&ssd_nr);
	}
}

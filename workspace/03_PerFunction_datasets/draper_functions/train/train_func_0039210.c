hdsp_read_gain (struct hdsp *hdsp, unsigned int addr)
{
	if (addr >= HDSP_MATRIX_MIXER_SIZE)
		return 0;

	return hdsp->mixer_matrix[addr];
}

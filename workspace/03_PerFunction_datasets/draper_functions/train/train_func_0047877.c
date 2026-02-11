same_processing(int a, int b) const
{
    int ai = _input_pidx[a], bi = _input_pidx[b];
    int ao = _output_pidx[a], bo = _output_pidx[b];
    int ani = _input_pidx[a+1] - ai, bni = _input_pidx[b+1] - bi;
    int ano = _output_pidx[a+1] - ao, bno = _output_pidx[b+1] - bo;
    if (ani != bni || ano != bno)
	return false;
    if (ani && memcmp(&_input_processing[ai], &_input_processing[bi], sizeof(int) * ani) != 0)
	return false;
    if (ano && memcmp(&_output_processing[ao], &_output_processing[bo], sizeof(int) * ano) != 0)
	return false;
    return true;
}

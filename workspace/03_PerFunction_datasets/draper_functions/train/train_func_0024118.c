read_char(void *data)
{
     next_char = get_input(data);
     if (next_char == 0 ||
	 next_char == EOF)
	  input_error = FFTW_FAILURE;
}

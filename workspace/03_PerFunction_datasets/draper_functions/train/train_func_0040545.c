swap_bytes_int(int *data, int length)
{

    int i;

    for (i=0; i<length; i++)
	data[i] = SWAPINT(data[i]);

}

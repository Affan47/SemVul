df_readline(double v[], int max)
{
    if (!data_fp && !df_pseudodata)
	return DF_EOF;

    if (df_read_binary)


	return df_readbinary(v, max);
    else
	return df_readascii(v, max);
}

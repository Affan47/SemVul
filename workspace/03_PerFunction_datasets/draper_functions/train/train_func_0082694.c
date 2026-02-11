timeconv_map_destroy (void)
{
    if (tconv_map.colnames != NULL) {
	strings_array_free(tconv_map.colnames, tconv_map.ncols);
    }
    if (tconv_map.fmt != NULL) {
	strings_array_free(tconv_map.fmt, 2);
    }
    timeconv_map_init();
}

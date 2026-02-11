open_tiff_input_file(t4_state_t *s, const char *file)
{
    if ((s->tiff.tiff_file = TIFFOpen(file, "r")) == NULL)
        return -1;
    return 0;
}

cff_write_FDArray_offsets(cff_writer_t *pcw, uint *FDArray_offsets,
                          int num_fonts)
{
    int j;

    cff_put_Index_header(pcw, num_fonts,
                         FDArray_offsets[num_fonts] - FDArray_offsets[0]);
    for (j = 1; j <= num_fonts; ++j)
        put_offset(pcw, FDArray_offsets[j] - FDArray_offsets[0] + 1);
}

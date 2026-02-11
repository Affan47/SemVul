sis_put(SegmentInfos *sis, FILE *stream)
{
    int i;
    fprintf(stream, "SegmentInfos {\n");
    fprintf(stream, "\tcounter = %"POSH_I64_PRINTF_PREFIX"d\n", sis->counter);
    fprintf(stream, "\tversion = %"POSH_I64_PRINTF_PREFIX"d\n", sis->version);
    fprintf(stream, "\tgeneration = %"POSH_I64_PRINTF_PREFIX"d\n", sis->generation);
    fprintf(stream, "\tformat = %d\n", sis->format);
    fprintf(stream, "\tsize = %d\n", sis->size);
    fprintf(stream, "\tcapa = %d\n", sis->capa);
    for (i = 0; i < sis->size; i++) {
        si_put(sis->segs[i], stream);
    }
    fprintf(stream, "}\n");
}

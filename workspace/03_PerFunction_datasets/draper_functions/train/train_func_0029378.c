ewrite_double_line(double * data, int nvals, int space, FILE * fp)
{
    int c;
    if( !data || nvals <= 0 || !fp ) return 1;

    fprintf(fp, "%*s", space, "");
    for( c = 0; c < nvals; c++ )
        fprintf(fp, "%f ", data[c]);
    fputc('\n', fp);

    return 0;
}

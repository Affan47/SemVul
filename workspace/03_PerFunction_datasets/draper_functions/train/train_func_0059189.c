fput_fraction(FILE *fp, int num, int den)
{
    fprintf(fp,"%d", num);

    if (den != 1)
        fprintf(fp, "/%d", den);
}

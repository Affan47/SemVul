main(int argc, char **argv)
{
    char *fname = argc>1 ? argv[1] : "rmme.bcf";
    write_bcf(fname);
    bcf_to_vcf(fname);
    return 0;
}

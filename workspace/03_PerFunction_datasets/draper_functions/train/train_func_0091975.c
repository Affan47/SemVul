ReadBinFile (FILE *file, void *buf, int nbytes, const char *fname)
{
    if (fread(buf, nbytes, 1, file) == -1)
	Die ("cannot read file \"%s\"", fname);

}

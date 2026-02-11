zfputs(char *line, zfp *zf) {
    if (zf->fp)
	return fputs(line, zf->fp);
    else
	return gzputs(zf->gz, line) ? 0 : EOF;
}

help()
{
    static char  *help_msg[] = {
 " -c --stdout      write on standard output, keep original files unchanged",
 " -d --decompress  decompress",
 " -f --force       force overwrite of output file and compress links",
 " -h --help        give this help",
 " -L --license     display software license",
#ifdef UNDOCUMENTED
 " -m --no-time     do not save or restore the original modification time",
 " -M --time        save or restore the original modification time",
#endif
 " -n --no-name     do not save or restore the original name and time stamp",
 " -N --name        save or restore the original name and time stamp",
 " -q --quiet       suppress all warnings",
 " -S .suf  --suffix .suf     use suffix .suf on compressed files",
 " -t --test        test compressed file integrity",
 " -v --verbose     verbose mode",
 " -V --version     display version number",
#ifdef SUPPORT_ZIP
 " -1 --fast        compress faster",
 " -9 --best        compress better",
 " file...          files to (de)compress. If none given, use standard input.",
#else
 " file...          files to decompress. If none given, use standard input.",
#endif
  0};
    char **p = help_msg;

    fprintf(stderr,"%s %s (%s)\n", progname, VERSION, REVDATE);
    usage();
    while (*p) fprintf(stderr, "%s\n", *p++);
}

usage()
{
    FileErrorHandler uerrh(stdout);
    uerrh.message("\
%<Otfinfo%> reports information about an OpenType font to standard output.\n\
Options specify what information to print.\n\
\n\
Usage: %s [-sfzpg | OPTIONS] [OTFFILES...]\n\n",
	   program_name);
    uerrh.message("\
Query options:\n\
  -s, --scripts                Report font%,s supported scripts.\n\
  -f, --features               Report font%,s GSUB/GPOS features.\n\
  -z, --optical-size           Report font%,s optical size information.\n\
  -p, --postscript-name        Report font%,s PostScript name.\n\
  -a, --family                 Report font%,s family name.\n\
  -v, --font-version           Report font%,s version information.\n\
  -i, --info                   Report font%,s names and designer/vendor info.\n\
  -g, --glyphs                 Report font%,s glyph names.\n\
  -t, --tables                 Report font%,s OpenType tables.\n\
  -T, --dump-table NAME        Output font%,s %<NAME%> table.\n\
\n\
Other options:\n\
      --script=SCRIPT[.LANG]   Set script used for --features [latn].\n\
  -V, --verbose                Print progress information to standard error.\n\
  -h, --help                   Print this message and exit.\n\
  -q, --quiet                  Do not generate any error messages.\n\
      --version                Print version number and exit.\n\
\n\
Report bugs to <ekohler@gmail.com>.\n");
}

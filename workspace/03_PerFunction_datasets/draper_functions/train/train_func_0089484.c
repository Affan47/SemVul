usage(FILE * fp)
{
    static char *message[] = {
	"Usage: ", CHA_PROG, " [options] [file...]\n",
	"    -s             partial analyzing mode\n",
	"  (how to print ambiguous results)\n",
	"    -b             show the best path (default)\n",
	"    -m             show all morphemes\n",
	"    -p             show all paths\n",
	"  (output format)\n",
	"    -f             show formatted morpheme data (default)\n",
	"    -e             show entire morpheme data\n",
	"    -c             show coded morpheme data\n",
	"    -d             show detailed morpheme data for Prolog\n",
	"    -v             show detailed morpheme data for VisualMorphs\n",
	"    -F format      show morpheme with formatted output\n",
	"    -Fh            print help of -F option\n",
	"  (miscellaneous)\n",
	"    -i encoding    character encoding.\n",
        "                   e: EUC-JP, s: Shift_JIS, ",
	"w: UTF-8, a: ISO-8859-1\n",
	"    -j             Japanese sentence mode\n",
	"    -o file        write output to `file'\n",
	"    -w width       specify the cost width\n",
	"    -C             use command mode\n",
	"    -r rc-file     use rc-file as a ", CHA_PROG,
	    "rc file other than the default\n",
	"    -R             with -D, do not read ", CHA_PROG,
	    "rc file, without -D, read the\n",
	"                   default chasenrc file `", RCPATH, "'\n",
	"    -L lang        specify languages\n",
	"    -O[c|s]        output with compound words or their segments\n",
	"    -lp            print the list of parts of speech\n",
	"    -lt            print the list of conjugation types\n",
	"    -lf            print the list of conjugation forms\n",
	"    -h             print this help\n",
	"    -V             print ", CHA_NAME, " version number\n",
	NULL
    };
    char **mes;

    cha_version(fp);
    if (fp)
	for (mes = message; *mes; mes++)
	    fputs(*mes, fp);
}

generate_header_of_codefile(const char *name)
{
    char *filename = NULL;

    if (codefile != NULL)
	abort();

    if (asprintf (&filename, "%s_%s.x", STEM, name) < 0 || filename == NULL)
	errx(1, "malloc");
    codefile = fopen (filename, "w");
    if (codefile == NULL)
	err (1, "fopen %s", filename);
    fprintf(logfile, "%s ", filename);
    free(filename);
    filename = NULL;
    fprintf (codefile,
	     "/* Generated from %s */\n"
	     "/* Do not edit */\n\n"
	     "#define  ASN1_LIB\n\n"
	     "#include <stdio.h>\n"
	     "#include <stdlib.h>\n"
	     "#include <time.h>\n"
	     "#include <string.h>\n"
	     "#include <errno.h>\n"
	     "#include <limits.h>\n"
	     "#include <%s>\n",
	     orig_filename,
	     type_file_string);

    fprintf (codefile,
	     "#include \"%s\"\n"
	     "#include \"%s\"\n",
	     header, privheader);
    fprintf (codefile,
	     "#include <asn1_err.h>\n"
	     "#include <der.h>\n"
	     "#include <asn1-template.h>\n\n");

    if (parse_units_flag)
	fprintf (codefile,
		 "#include <parse_units.h>\n\n");

}

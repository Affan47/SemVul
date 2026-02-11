code_header()
{
	FIELD *f;
	u_int i;

	fprintf(hfp, "/*\n");
	fprintf(hfp, " *  DO NOT EDIT: automatically built by %s.\n", progname);
	fprintf(hfp, " *\n");
	fprintf(hfp, " * Record structure.\n");
	fprintf(hfp, " */\n");
	fprintf(hfp, "typedef struct __DbRecord {\n");


	fprintf(hfp, "\t/*\n");
	fprintf(hfp, "\t * Indexed fields\n");
	fprintf(hfp, "\t */\n");
	for (f = fields, i = 0; f->name != NULL; ++f) {
		if (f->type == NOTSET)
			continue;
		if (i != 0)
			fprintf(hfp, "\n");
		fprintf(hfp, "#define	SQLITE_DB_INDX_%s\t%d\n", f->upper, i + 1);
		switch (f->type) {
		case NOTSET:

			abort();
			break;
		case DOUBLE:
			fprintf(hfp, "\tdouble\t\t %s", f->name);
            if (f->array)
                fprintf(hfp, "[%u]", f->array_len);
            fprintf(hfp, ";\n");
			break;
		case STRING:
			fprintf(hfp, "\tchar\t\t%s", f->name);
            if(f->array)
                fprintf(hfp, "[%u]", f->array_len);
            fprintf(hfp, "[%u];\n", f->size);
			break;
		case UNSIGNED_LONG:
			fprintf(hfp, "\tu_int32_t\t\t %s", f->name);
            if (f->array)
                fprintf(hfp, "[%u]", f->array_len);
            fprintf(hfp,";\n");
			break;
        case DATE:
            fprintf(hfp, "\tstruct tm\t\t %s;\n", f->name);
            if (f->array)
                fprintf(hfp, "[%u]", f->array_len);
		}
        ++i;
	}
	fprintf(hfp, "} DbRecord;\n");
    fprintf(hfp, "#define SQLITE_DB_NUMFIELDS\t%d", i+1);

	return (0);
}

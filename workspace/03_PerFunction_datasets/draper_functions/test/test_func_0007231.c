pr_file(FILE *fp)
{
    if (filename != NULL) {
	fputs("%%\nfile ", fp);
	pr_string(fp, filename);
	fputs(";\n", fp);
    }
    if (option != NULL) {
	fputs("%%\noption ", fp);
	pr_string(fp, option);
	fputs(";\n", fp);
    }
    pr_language_tag(fp, lang_tag);

    fprintf(fp, "%%%%\nsystem {%1d,%1d}\n\n", pc_count, pe_count);
}

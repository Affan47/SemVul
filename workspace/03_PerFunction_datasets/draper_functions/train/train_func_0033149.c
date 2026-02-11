handle_incbin(astnode *n)
{
    FILE *fp;
    unsigned char *data;
    int size;
    char errs[512];

    astnode *file = astnode_get_child(n, 0);
    const char *filename = file->string;
    int quoted_form = (astnode_get_type(file) == STRING_NODE) ? 1 : 0;

    fp = open_included_file(filename, quoted_form, NULL);
    if (fp) {

        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        rewind(fp);
        if (size > 0) {

            data = (unsigned char *)malloc(size);

            fread(data, 1, size, fp);

            astnode_add_sibling(n, astnode_create_binary(data, size, n->loc) );
        }

        fclose(fp);
    } else {

        sprintf(errs, "could not open '%s' for reading", file->string);
        yyerror(errs);
    }
}

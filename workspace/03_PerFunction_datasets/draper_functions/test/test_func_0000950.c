print_header_line(FILE *fp, HeaderLine *hline)
{
    list_t *tags = hline->tags;
    HeaderTag *tag;

    fprintf(fp, "@%c%c", hline->type[0],hline->type[1]);
    while (tags)
    {
        tag = tags->data;

        fprintf(fp, "\t");
        if ( tag->key[0]!=' ' || tag->key[1]!=' ' )
            fprintf(fp, "%c%c:", tag->key[0],tag->key[1]);
        fprintf(fp, "%s", tag->value);

        tags = tags->next;
    }
    fprintf(fp,"\n");
}

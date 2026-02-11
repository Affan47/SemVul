xbaeParseColumnLabel(label, lines)
String label;
ColumnLabelLines lines;
{
    char *nl;


    lines->lines = 1;
    nl = label;
    while ((nl = strchr(nl, '\n')) != NULL)
    {
        nl++;
        lines->lines++;
    }


    lines->lengths = (int *) XtMalloc(lines->lines * sizeof(int));


    if (lines->lines == 1)
        lines->lengths[0] = strlen(label);
    else
    {
        int i;

        nl = label;
        i = 0;
        while ((nl = strchr(nl, '\n')) != NULL)
        {
            lines->lengths[i] = nl - label;
            nl++;
            label = nl;
            i++;
        }
        lines->lengths[i] = strlen(label);
    }
}

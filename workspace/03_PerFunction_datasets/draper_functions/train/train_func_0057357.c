print_short(
    unsigned int filename_width,
    int show_size,
    int show_date,
    int show_owner,
    int show_protection,
    int single_column,
    int entries_per_line,
    long size,
    char *name,
    char *owner,
    char *cdt,
    char *prot,
    int *printed
)
{
    printf("%-*s", filename_width, name);
    if (show_size || show_date || show_owner || show_protection)
	printf("  ");
    if (single_column)
    {
	if (strlen(name) >= filename_width &&
	    (show_protection || show_date ||
	     show_owner || show_date || show_size))
	{
	    printf("\n%-*s  ",filename_width, "");
	}
	if (show_size)
	    printf("%7ld ", size);
	if (show_date)
	    printf("%s ", cdt);
	if (show_owner)
	    printf("%s ", owner);
	if (show_protection)
	    printf("%s", prot);
	printf("\n");
    }
    else
    {
	if (++(*printed) >= entries_per_line)
	{
	    printf("\n");
	    *printed = 0;
	}


	if (strlen(name) >= filename_width && *printed)
	{
	    if (*printed+1 >= entries_per_line)
	    {
		printf("\n");
		*printed = 0;
	    }
	    else
	    {
		printf("%-*s",(int)(filename_width-(strlen(name)-filename_width)), "");
	    }
	    ++(*printed);
	}
    }
}

create_filter_text()
{
    filter_text = (char **) calloc(FILTER_MODES,sizeof (char *));
    for(int i=0;i<FILTER_MODES;i++) filter_text[i] = new char[100];

    strcpy(filter_text[DONT_COUNT],           "don't count (ignore)                              ");
    strcpy(filter_text[SKIP_COLUMN_IF_MAX],   "if occurs most often => forget whole column       ");
    strcpy(filter_text[SKIP_COLUMN_IF_OCCUR], "if occurs => forget whole column                  ");
    strcpy(filter_text[COUNT_DONT_USE_MAX],   "count, but do NOT use as maximum                  ");
    strcpy(filter_text[TREAT_AS_UPPERCASE],   "treat as uppercase character                      ");
    strcpy(filter_text[TREAT_AS_REGULAR],     "treat as regular character                        ");
}

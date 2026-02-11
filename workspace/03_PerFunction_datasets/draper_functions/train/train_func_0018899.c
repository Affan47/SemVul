pr_option_kind(FILE *fp)
{
    int i;
    for (i=0 ; i<(int)(sizeof(option_list)/sizeof(struct _option)) ; i++) {
        putc('-', fp);
        fputs(option_list[i].option_str, fp);
        putc('\n', fp);
    }
}

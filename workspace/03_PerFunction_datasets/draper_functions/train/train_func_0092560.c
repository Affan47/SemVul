reset()
{
    for(int i=0; i < num_errors; i++)
        free(elist[i]);
    for(int j=0; j <= NVPARSE_MAX_ERRORS; j++)
        elist[j] = 0;
    num_errors = 0;
}

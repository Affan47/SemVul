is_a_kmc()
{
    int 	i;
    int 	isakmc=0;

    for (i = 0; i < sizeof(kmc_names) / sizeof(char *); i++) {
	if (!strncmp(product,kmc_names[i],strlen(kmc_names[i]))) isakmc = 1;
       }
    return(isakmc);
}

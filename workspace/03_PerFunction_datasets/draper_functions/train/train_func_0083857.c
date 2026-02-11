print_args(int ac, char **av)
{
    int     i;

    printf("print_args: [%d]", ac);
    for (i = 0; i < ac; i++)
        printf(" \"%s\"", av[i]);
    fputc('\n', stdout);
}

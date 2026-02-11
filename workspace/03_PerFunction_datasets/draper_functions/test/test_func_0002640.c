winargs(int argc, char **argv, char *buffer)
{
    if (argc == 2)
    {
        if (!(strlen(argv[1]) < MaxBuffer - 1))
            return 0;

        strcpy(buffer, argv[1]);
    }

    return (argc == 2);
}

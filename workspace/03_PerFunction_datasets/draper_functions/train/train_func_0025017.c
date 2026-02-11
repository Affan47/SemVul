print_string_value(char * aspect, char * value)
{
    printf("%s: ", aspect);

    if (strchr(value, '\n') != NULL)
    {
        putchar('"');

        while (*value)
        {
            if (*value == '"')
            {
                putchar('\\');
            }
            putchar(*value);
            value++;
        }
        putchar('"');
        putchar('\n');
    }
    else
    {
        printf("%s\n", value);
    }
}

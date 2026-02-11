is_valid_termination(char* value)
{
    int len;
    int end;
    len = strlen(value);

    if (value == NULL)
    {
        return -1;
    }


    if (len < 1 || value[len - 1] != '\n')
    {
        return -1;
    }

    end = len - 1;

    if (end > 1 && value[end - 1] == '\r')
    {
        end--;
    }

    return end;
}

std_get_company_name(char *input)
{
    int i = 0;
    while (isalpha(input[i]) || input[i] == '@' || input[i] == '&') {
        i++;
    }

    return i;
}

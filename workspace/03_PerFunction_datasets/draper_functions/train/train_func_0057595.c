StripSpecial(char *string)
{
    int i,j,len;
    i=0;

    len = strlen(string);
    for(j=0;j<len;j++)
    {
        if(string[j] == '"')
            string[j] = '`';
        else if(string[j] == '{')
            string[j] = '(';
        else if(string[j] == '}')
            string[j] = ')';
    }

}

indent_string(const char * str)
{
    char * new_line;
    char * old_line;
    char * output;
    int i=1;

    for (new_line = (char *) str; new_line != NULL; new_line = strchr(new_line+1, '\n'))
    {
        i++;
    }

    output = malloc(strlen(str) + (i*4) + 1);
    i = 0;

    for (new_line = strchr(str, '\n'), old_line = (char *) str;
         new_line != NULL;
         old_line = new_line+1, new_line = strchr(new_line+1, '\n'))
    {
        memcpy(output+i, "    ", 4);
        i += 4;
        memcpy(output+i, old_line, new_line - old_line);
        i += new_line - old_line;
        output[i++] = '\n';
    }
    output[i] = 0;

    return output;
}

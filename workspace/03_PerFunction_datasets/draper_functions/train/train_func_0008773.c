build_exec_line(char* handler, char* path, char* name)
{
    char* sanefilename;
    char* handlerline;
    char* replacename;
    char* percentmod = NULL;
    char* postpercent = NULL;
    char* percentloc = NULL;
    int didreplace = 0;
    int percentoffset;
    int reallocsize;


    sanefilename = malloc(strlen(path) + strlen(name) + 4);
    sprintf(sanefilename, "'%s/%s'", path, name);

    handlerline = strdup(handler);


    while ((percentloc = strstr(handlerline, "%")))
    {
        percentmod = percentloc+1;


        if (percentmod[0] == '%')
            replacename = sanefilename;
        else if (percentmod[0] == 'F' || percentmod[0] == 'f')
            replacename = name;
        else if (percentmod[0] == 'D' || percentmod[0] == 'd')
            replacename = path;
        else
        {
            log_write("Error: %%%c is not a valid substitution string\n",percentmod[0]);
        }

        percentoffset = percentloc - handlerline;
        didreplace = 1;
        postpercent = strdup(percentloc+2);


        reallocsize = strlen(handlerline) - 2 + strlen(replacename) + 1;
        handlerline = realloc(handlerline, reallocsize);


        strncpy(handlerline+percentoffset, replacename, strlen(replacename) + 1);
        strncat(handlerline, postpercent, strlen(postpercent));
        free(postpercent);
    }


    if (!didreplace)
    {
        handlerline = realloc(handlerline, strlen(handlerline) + 1 + strlen(sanefilename) + 1);
        strcat(handlerline, " ");
        strcat(handlerline, sanefilename);
    }

    free(sanefilename);

    return handlerline;
}

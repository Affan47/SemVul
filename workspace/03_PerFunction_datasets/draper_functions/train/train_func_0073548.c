_cmdparser_find(const char* name)
{
    size_t max, min, guess;
    int cmp;
    min = 0;
    max = _cmdparser_nb - 1;

    while(max - min > 1) {
        guess = (max + min) / 2;
        cmp = strcmp(_cmdparser_cmds[guess].name, name);
        if(cmp == 0)
            return &_cmdparser_cmds[guess];
        else if(cmp < 0)
            min = guess;
        else
            max = guess;
    }

    if(strcmp(_cmdparser_cmds[min].name, name) == 0)
        return &_cmdparser_cmds[min];
    else if(strcmp(_cmdparser_cmds[max].name, name) == 0)
        return &_cmdparser_cmds[max];
    else
        return NULL;
}

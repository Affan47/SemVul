eco_FromString(const char * ecoStr)
{
    ecoT eco = ECO_None;


    if(*ecoStr >= 'A'  &&  *ecoStr <= 'E')
    {
        eco = (*ecoStr - 'A') * 13100;
    }
    else if(*ecoStr >= 'a'  &&  *ecoStr <= 'e')
    {
        eco = (*ecoStr - 'a') * 13100;
    }
    else
    {
        return 0;
    }
    ecoStr++;
    if(! *ecoStr)
    {
        return eco + 1;
    }

    if(*ecoStr < '0'  ||  *ecoStr > '9')
    {
        return 0;
    }
    eco += (*ecoStr - '0') * 1310;
    ecoStr++;
    if(! *ecoStr)
    {
        return eco + 1;
    }

    if(*ecoStr < '0'  ||  *ecoStr > '9')
    {
        return 0;
    }
    eco += (*ecoStr - '0') * 131;
    ecoStr++;


    if(*ecoStr >= 'a'  &&  *ecoStr <= 'z')
    {
        eco++;
        eco += (*ecoStr - 'a') * 5;
        ecoStr++;
        if(*ecoStr >= '1'  &&  *ecoStr <= '4')
        {
            eco += *ecoStr - '0';
        }
    }
    return eco + 1;
}

GetPOS(char *sensekey)
{
    int pos;


    while (*sensekey++ != '%');
    sscanf(sensekey, "%1d", &pos);
    return(pos == SATELLITE ? ADJ : pos);
}

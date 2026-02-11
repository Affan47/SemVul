enth_string(int i)
{
    static char enth[10];

    enth[0] = '\0';

    switch (i % 10) {

      case 1:
        if( (i % 100 ) == 11)
          snprintf(enth, sizeof(enth),"%dth", i);
        else
          snprintf(enth, sizeof(enth),"%dst", i);
        break;

      case 2:
        if ((i % 100) == 12)
          snprintf(enth, sizeof(enth), "%dth",i);
        else
          snprintf(enth, sizeof(enth), "%dnd",i);
        break;

      case 3:
        if(( i % 100) == 13)
          snprintf(enth, sizeof(enth), "%dth",i);
        else
          snprintf(enth, sizeof(enth), "%drd",i);
        break;

      default:
        snprintf(enth, sizeof(enth),"%dth",i);
        break;
    }
    return(enth);
}

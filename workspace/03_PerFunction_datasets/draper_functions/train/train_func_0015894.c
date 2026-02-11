ValidateZoneName(const char* &start)
{
    string zoneName="";
    Valid=true;
    if (*start==':')
    {
        Valid=false;
        return zoneName;
    }
    while(!( isdigit(*start)||(*start==',')||
             (*start=='+')||(*start=='-')||(!*start)
         ) )
    {
        zoneName=zoneName+*start;
        start++;
    }
    if (zoneName.length()<3) {Valid=false; return "";};
    return zoneName;
}

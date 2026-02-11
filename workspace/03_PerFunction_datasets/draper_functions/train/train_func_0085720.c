alma_key_word(line, index, key, length)
     char    *line;
     int index;
     char    *key;
     int length;
{
    int indi, indj;

    if(line==NULL)  { key[0]='\0'; return(index); }
    for(indi=index, indj=0;
        (index-indi)<length&&line[indi]!='>'
            &&line[indi]!='\n'&&line[indi]!='\0';
        indi++, indj++)
        key[indj] = line[indi];
    key[indj] = '\0';
    if(line[indi]=='>') return(indi+1);
    else return(indi);
}

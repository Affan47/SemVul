lk_playlist_escape(char * data, unsigned int length)
{
    char * str;
    unsigned int i, count;

    str=malloc(length*5+1);
    for(i=0,count=0; i < length; i++, count++){
        if(data[i]=='\\'){
            str[count]='\\';
            str[++count]='\\';
        } else if(data[i]=='\n'){
            str[count]='\\';
            str[++count]='n';
        } else if(data[i]>=32 || data[i]<0) str[count]=data[i];
        else {
            str[count]='\\';
            str[++count]='x';
            if((data[i]/16)<10) str[++count]=(data[i]/16)+'0';
            else str[++count]=(data[i]/16)+55;
            if((data[i]%16)<10) str[++count]=(data[i]%16)+'0';
            else str[++count]=(data[i]%16)+55;
        }
    }
    str[count++]=0;
    str=(char *)realloc(str, count);
    return str;
}

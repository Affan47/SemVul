uf_remove_whitespace(char *str){
    int z=0;
    if(str==NULL)
        str=strdup(" ");
    while(isspace(str[z])&&str[z])
        z++;
    str+=z;
    return str;
}

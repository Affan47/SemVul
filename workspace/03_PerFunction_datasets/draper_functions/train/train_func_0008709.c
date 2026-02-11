rindex(const char* str, int end_index) const {
    if (str==NULL || *str == '\0' || length()==0 || end_index>=length())
        return -1;
    int slen=strlen(str);
    if (end_index<0) end_index=my_data->length-1;


    if (end_index>=0 && end_index<slen-1) return -1;
    for (int i=end_index-slen+1;i>=0;i--) {
       if (memcmp((void*)(my_data->chars+i),(void*)str, slen)==0)
           return i;
       }
    return -1;
}

sinfo_paf_query(
        char    *   filename,
        char    *   key)
{
    static char value[ASCIILINESZ];
    FILE    *    paf ;
    char        line[ASCIILINESZ+1];
    char        val[ASCIILINESZ+1];
    char        head[ASCIILINESZ+1];
    int            found ;
    int            len ;


    if (filename==NULL || key==NULL) return NULL ;


    if (sinfo_is_paf_file(filename)!=1) {
        sinfo_msg_error("not a PAF file: [%s]", filename);
        return NULL ;
    }


    paf = fopen(filename, "r");
    if (paf==NULL) {
        sinfo_msg_error("opening [%s]", filename);
        return NULL ;
    }

    found = 0 ;
    while (fgets(line, ASCIILINESZ, paf)!=NULL) {
        sscanf(line, "%[^ ]", head);
        if (!strcmp(head, key)) {

            sscanf(line, "%*[^ ] %[^;]", value);
            found ++ ;
            break ;
        }
    }
    if (!found) {
      fclose(paf);
      return NULL ;
    }


    strcpy(val, sinfo_strcrop(value));

    len = strlen(val);
    if (val[0]=='\"' && val[len-1]=='\"') {
        strncpy(value, val+1, len-2);
        value[len-2]=(char)0;
    } else {
        strcpy(value, val);
    }
    if(paf!=NULL){
       fclose(paf);
    }
    return value ;
}

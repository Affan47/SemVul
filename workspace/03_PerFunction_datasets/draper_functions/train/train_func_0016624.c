AlignmentView_string_is_empty(GString *str, gint pos,
                                              gint width){
    register gint i;
    for(i = 0; i < width; i++)
        if(str->str[pos+i] != ' ')
            return FALSE;
    return TRUE;
    }

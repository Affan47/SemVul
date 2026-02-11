AlignmentView_replace_padding(GString *str, gint pos, gint width){
    register gint i;
    for(i = 0; i < width; i++){
        if(str->str[pos+i] == '^')
            str->str[pos+i] = ' ';
        }
    return;
    }

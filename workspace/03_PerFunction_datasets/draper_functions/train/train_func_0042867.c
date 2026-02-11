fasta_index_seek_to_char(FILE *fp, gchar c){
    register gint ch;
    while((ch = getc(fp)) != EOF){
        if(ch == c)
            break;
        }
    return ch;
    }

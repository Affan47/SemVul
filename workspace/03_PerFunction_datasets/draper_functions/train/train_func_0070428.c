replace(char *text,long position, int direction) {
    int text_len = strlen(text);
    int i;
    if (direction>=0){

        if ((position + text_len > seq_len) || (position > seq_len)) {
            return new AD_ERR("AD_SEQ.replace() ERROR ! Replace after end of sequence !");
        }
        for ( i = 0; i < text_len ; i ++) {
            seq[i+position] = text[i];
        }
    }else{
        if ((position - text_len < 0 ) || (position > seq_len)) {
        return new AD_ERR("AD_SEQ.replace() ERROR ! Replace before start of sequence !");
    }
    for ( i = 0; i < text_len ; i ++) {
        seq[position - i - 1] = text[i];
    }
}
return 0;
}

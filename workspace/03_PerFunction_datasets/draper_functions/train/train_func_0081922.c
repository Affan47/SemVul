process_COM (const uchar * Data, int length)
{
    int ch;
    char Comment[MAX_COMMENT_SIZE+1];
    int nch;
    int a;

    nch = 0;

    if (length > MAX_COMMENT_SIZE) length = MAX_COMMENT_SIZE;

    for (a=2;a<length;a++){
        ch = Data[a];

        if (ch == '\r' && Data[a+1] == '\n') continue;

        if (ch >= 32 || ch == '\n' || ch == '\t'){
            Comment[nch++] = (char)ch;
        }else{
            Comment[nch++] = '?';
        }
    }

    Comment[nch] = '\0';

    if (ShowTags){
        printf("COM marker comment: %s\n",Comment);
    }

    strcpy(ImageInfo.Comments,Comment);
}

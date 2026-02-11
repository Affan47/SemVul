debugflag(char * result, unsigned short flag) {
    char * st = encode_flag(flag);
    mystrcat(result, " ", MAXLNLEN);
    mystrcat(result, MORPH_FLAG, MAXLNLEN);
    if (st) {
        mystrcat(result, st, MAXLNLEN);
        free(st);
    }
}

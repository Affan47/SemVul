prolog(outfp) FILE *outfp; {
    int c;
    while ((c = *txt1++)     != '\0') putc(c,outfp);
    while ((c = *fname++)    != '\0') putc(c,outfp);
    while ((c = *txt2++)     != '\0') putc(c,outfp);
    while ((c = *tbl_type++) != '\0') putc(c,outfp);
    while ((c = *txt2a++)    != '\0') putc(c,outfp);
    while ((c = *txt2b++)    != '\0') putc(c,outfp);
}

w_string(char *s, int n, WFILE *p)
{
    if (p->fp != NULL) {
        fwrite(s, 1, n, p->fp);
    }
    else {
        while (--n >= 0) {
            w_byte(*s, p);
            s++;
        }
    }
}

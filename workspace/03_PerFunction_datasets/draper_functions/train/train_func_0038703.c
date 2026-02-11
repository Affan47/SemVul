binbuf_gettext(t_binbuf *x, char **bufp, int *lengthp)
{
    char *buf = getbytes(0), *newbuf;
    int length = 0;
    char string[MAXPDSTRING];
    t_atom *ap;
    int indx;

    for (ap = x->b_vec, indx = x->b_n; indx--; ap++)
    {
        int newlength;
        if ((ap->a_type == A_SEMI || ap->a_type == A_COMMA) &&
                length && buf[length-1] == ' ') length--;
        atom_string(ap, string, MAXPDSTRING);
        newlength = length + strlen(string) + 1;
        if (!(newbuf = resizebytes(buf, length, newlength))) break;
        buf = newbuf;
        strcpy(buf + length, string);
        length = newlength;
        if (ap->a_type == A_SEMI) buf[length-1] = '\n';
        else buf[length-1] = ' ';
    }
    if (length && buf[length-1] == ' ')
    {
        if (newbuf = t_resizebytes(buf, length, length-1))
        {
            buf = newbuf;
            length--;
        }
    }
    *bufp = buf;
    *lengthp = length;
}

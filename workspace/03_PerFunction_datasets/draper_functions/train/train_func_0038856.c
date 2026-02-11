decoding_fgets(char *s, int size, struct tok_state *tok)
{
    char *line = NULL;
    int badchar = 0;
    for (;;) {
        if (tok->decoding_state < 0) {


            line = fp_readl(s, size, tok);
            break;
        } else if (tok->decoding_state > 0) {

            line = Py_UniversalNewlineFgets(s, size,
                                            tok->fp, NULL);
            break;
        } else {


            if (!check_bom(fp_getc, fp_ungetc, fp_setreadl, tok))
                return error_ret(tok);
            assert(tok->decoding_state != 0);
        }
    }
    if (line != NULL && tok->lineno < 2 && !tok->read_coding_spec) {
        if (!check_coding_spec(line, strlen(line), tok, fp_setreadl)) {
            return error_ret(tok);
        }
    }
#ifndef PGEN


    if (line && !tok->encoding) {
        unsigned char *c;
        for (c = (unsigned char *)line; *c; c++)
            if (*c > 127) {
                badchar = *c;
                break;
            }
    }
    if (badchar) {
        char buf[500];


        sprintf(buf,
            "Non-ASCII character '\\x%.2x' "
            "in file %.200s on line %i, "
            "but no encoding declared; "
            "see http://www.python.org/peps/pep-0263.html for details",
            badchar, tok->filename, tok->lineno + 1);
        PyErr_SetString(PyExc_SyntaxError, buf);
        return error_ret(tok);
    }
#endif
    return line;
}

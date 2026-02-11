readone(LVAL fptr, LVAL *pval)
{
    LVAL val,type;
    int ch;

#ifdef DEBUG_INPUT
    if (debug_input_fp) {
        int c = getc(debug_input_fp);
        ungetc(c, debug_input_fp);
    }
#endif

    if ((ch = xlgetc(fptr)) == EOF)
        return (EOF);


    if ((type = tentry(ch)) == k_wspace)
        return (FALSE);


    else if (type == k_const) {
        xlungetc(fptr,ch);
        *pval = psymbol(fptr);
        return (TRUE);
    }


    else if (type == k_sescape || type == k_mescape) {
        xlungetc(fptr,ch);
        *pval = psymbol(fptr);
        return (TRUE);
    }


    else if (consp(type)) {
        if ((val = callmacro(fptr,ch)) && consp(val)) {
            *pval = car(val);
            return (TRUE);
        }
        else
            return (FALSE);
    }


    else {
        xlerror("illegal character",cvfixnum((FIXTYPE)ch));


        return (FALSE);
    }
}

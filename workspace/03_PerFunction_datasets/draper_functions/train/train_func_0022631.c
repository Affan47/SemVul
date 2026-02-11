xmlSchemaComparePreserveCollapseStrings(const xmlChar *x,
                                        const xmlChar *y,
                                        int invert)
{
    int tmp;


    while IS_WSP_BLANK_CH(*y)
        y++;

    while ((*x != 0) && (*y != 0)) {
        if IS_WSP_BLANK_CH(*y) {
            if (! IS_WSP_SPACE_CH(*x)) {


                if ((*x - 0x20) < 0) {
                    if (invert)
                        return(1);
                    else
                        return(-1);
                } else {
                    if (invert)
                        return(-1);
                    else
                        return(1);
                }
            }
            x++;
            y++;


            while IS_WSP_BLANK_CH(*y)
                y++;
        } else {
            tmp = *x++ - *y++;
            if (tmp < 0) {
                if (invert)
                    return(1);
                else
                    return(-1);
            }
            if (tmp > 0) {
                if (invert)
                    return(-1);
                else
                    return(1);
            }
        }
    }
    if (*x != 0) {
         if (invert)
             return(-1);
         else
             return(1);
    }
    if (*y != 0) {


        while IS_WSP_BLANK_CH(*y)
            y++;
        if (*y != 0) {
            if (invert)
                return(1);
            else
                return(-1);
        }
    }
    return(0);
}

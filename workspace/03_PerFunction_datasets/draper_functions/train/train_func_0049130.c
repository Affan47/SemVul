CORD_iter5(CORD x, size_t i, CORD_iter_fn f1,
			 CORD_batched_iter_fn f2, void * client_data)
{
	int result;
    if (x == 0) return(0);
    if (CORD_IS_STRING(x)) {
    	register const char* p = x+i;

    	if (*p == '\0') ABORT("2nd arg to CORD_iter5 too big");
        if (f2 != CORD_NO_FN) {
            return((*f2)(p, client_data));
        } else {
	    while (*p) {
                if (result=(*f1)(*p, client_data))
					return result;
                p++;
	    }
	    return(0);
        }
    } else if (IS_CONCATENATION(x)) {
    	register struct Concatenation * conc = &(((CordRep *)x) -> concatenation);
    	if (i > 0) {
    	    register size_t left_len = LEFT_LEN(conc);

    	    if (i >= left_len) {
    	        return(CORD_iter5(conc -> right, i - left_len, f1, f2,
    	        		  client_data));
    	    }
    	}
		result=CORD_iter5(conc -> left, i, f1, f2, client_data);
    	if (result) return result;
    	return(CORD_iter5(conc -> right, 0, f1, f2, client_data));
    } else  {
        register struct Function * f = &(((CordRep *)x) -> function);
        register size_t j;
        register size_t lim = f -> len;

        for (j = i; j < lim; j++) {
            if (result=(*f1)((*(f -> fn))(j, f -> client_data), client_data))
				return result;
        }
        return(0);
    }
}

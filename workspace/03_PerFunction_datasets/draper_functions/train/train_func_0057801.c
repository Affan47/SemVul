fl_string_split(value_t *args, u_int32_t nargs)
{
    argcount("string.split", nargs, 2);
    char *s = tostring(args[0], "string.split");
    char *delim = tostring(args[1], "string.split");
    size_t len = cv_len((cvalue_t*)ptr(args[0]));
    size_t dlen = cv_len((cvalue_t*)ptr(args[1]));
    size_t ssz, tokend=0, tokstart=0, i=0;
    value_t first=FL_NIL, c=FL_NIL, last;
    size_t junk;
    fl_gc_handle(&first);
    fl_gc_handle(&last);

    do {

        tokstart = tokend = i;
        while (i < len &&
               !u8_memchr(delim, u8_nextmemchar(s, &i), dlen, &junk))
            tokend = i;
        ssz = tokend - tokstart;
        last = c;
        c = fl_cons(cvalue_string(ssz), FL_NIL);


        s = cv_data((cvalue_t*)ptr(args[0]));
        delim = cv_data((cvalue_t*)ptr(args[1]));

        if (ssz) memcpy(cv_data((cvalue_t*)ptr(car_(c))), &s[tokstart], ssz);


        if (last == FL_NIL)
            first = c;
        else
            ((cons_t*)ptr(last))->cdr = c;


    } while (i < len || (i==len && (tokend!=i)));
    fl_free_gc_handles(2);
    return first;
}

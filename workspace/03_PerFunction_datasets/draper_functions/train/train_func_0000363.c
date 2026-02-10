_cx_string_rtrim(cx_string *self)
{

    cxchar *tmp = NULL;
    cxsize  i = 0;


    cx_assert(self != NULL);

    tmp = self->data + self->sz - 1;

    while (isspace((cxint)*tmp)) {
        tmp--;
        i++;
    }

    *++tmp = (cxchar) '\0';
    self->sz -= i;

    return self;

}

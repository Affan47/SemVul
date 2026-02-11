strio_set_lineno(VALUE self, VALUE lineno)
{
    StringIO(self)->lineno = NUM2LONG(lineno);
    return lineno;
}

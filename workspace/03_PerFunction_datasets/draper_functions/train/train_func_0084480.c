dlappend(Datalist* dl, Constant* constant)
{
    if(dl->length >= dl->alloc) dlextend(dl);
    if(constant == NULL) constant = &nullconstant;
    dl->data[dl->length++] = *constant;
}

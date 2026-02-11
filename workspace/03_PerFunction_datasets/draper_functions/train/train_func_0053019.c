oc_inq_dasattr(OCconnection conn, OCobject node0, unsigned int i,
               OCtype* primtypep, char** valuep)
{
    OCstate* state;
    OCnode* attr;
    unsigned int nvalues;
    OCVERIFY(OCstate*,state,conn);
    OCDEREF(OCstate*,state,conn);
    OCVERIFY(OCnode*,attr,node0);
    OCDEREF(OCnode*,attr,node0);

    if(attr->octype != OC_Attribute) return OC_EINVAL;
    nvalues = oclistlength(attr->att.values);
    if(i >= nvalues) return OC_EINVAL;
    if(valuep) *valuep = nulldup((char*)oclistget(attr->att.values,i));
    if(primtypep) *primtypep = attr->etype;
    return OC_NOERR;
}

oc_inq_object(OCconnection conn,
	  OCobject node0,
	  char** namep,
	  OCtype* objecttypep,
	  OCtype* primitivetypep,
	  OCobject* containerp,
	  unsigned int* rankp,
	  unsigned int* subnodesp,
	  unsigned int* nattrp)
{
    OCstate* state;
    OCnode* node;
    OCVERIFY(OCstate*,state,conn);
    OCDEREF(OCstate*,state,conn);
    OCVERIFY(OCnode*,node,node0);
    OCDEREF(OCnode*,node,node0);

    if(namep) *namep = nulldup(node->name);
    if(objecttypep) *objecttypep = node->octype;
    if(primitivetypep) *primitivetypep = node->etype;
    if(rankp) *rankp = node->array.rank;
    if(containerp) *containerp = (OCobject)node->container;
    if(subnodesp) *subnodesp = oclistlength(node->subnodes);
    if(nattrp) {
        if(node->octype == OC_Attribute) {
            *nattrp = oclistlength(node->att.values);
        } else {
            *nattrp = oclistlength(node->attributes);
	}
    }
    return OC_NOERR;
}

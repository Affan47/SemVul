oc_inq_subnodes(OCconnection conn, OCobject node0, OCobject** subnodesp)
{
    OCstate* state;
    OCnode* node;
    OCobject* subnodes = NULL;
    unsigned int len;
    OCVERIFY(OCstate*,state,conn);
    OCDEREF(OCstate*,state,conn);
    OCVERIFY(OCnode*,node,node0);
    OCDEREF(OCnode*,node,node0);

    len = oclistlength(node->subnodes);
    if(len > 0) {
	unsigned int i;
	subnodes = (OCobject*)occalloc(sizeof(OCobject),len+1);
	for(i=0;i<len;i++) {
	    OCnode* ocnode = (OCnode*)oclistget(node->subnodes,i);
	    subnodes[i] = (OCobject)ocnode;
	}
        subnodes[len] = OCNULL;
    }
    if(subnodesp) *subnodesp = subnodes;
    return OC_NOERR;
}

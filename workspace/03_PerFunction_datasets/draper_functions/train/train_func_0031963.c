dap_makesequence(DAPparsestate* state, Object name, Object members)
{
    OCnode* node;
    char* dupname;
    if((dupname=scopeduplicates((OClist*)members)) != NULL) {
        dap_parse_error(state,"Duplicate sequence member names in same scope: %s.%s",(char*)name,dupname);
	return (Object)NULL;
    }
    node = newocnode(name,OC_Sequence,state);
    node->subnodes = members;
    addedges(node);
    return node;
}

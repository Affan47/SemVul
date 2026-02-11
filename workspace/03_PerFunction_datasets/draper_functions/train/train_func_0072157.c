dap_makestructure(DAPparsestate* state, Object name, Object dimensions, Object fields)
{
    OCnode* node;
    char* dupname;
    if((dupname=scopeduplicates((OClist*)fields))!= NULL) {
        dap_parse_error(state,"Duplicate structure field names in same scope: %s.%s",(char*)name,dupname);
	return (Object)NULL;
    }
    node = newocnode(name,OC_Structure,state);
    node->subnodes = fields;
    dimension(node,(OClist*)dimensions);
    addedges(node);
    return node;
}

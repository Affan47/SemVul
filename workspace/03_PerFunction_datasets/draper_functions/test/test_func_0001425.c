Lookup(xmap_p<BeNode>& dict,const char *name,BeNode::be_type_t type)
{
   BeNode *node=dict.lookup(name);
   if(!node) {
      SetError(xstring::format("Meta-data: `%s' key missing",name));
      return 0;
   }
   if(node->type!=type) {
      SetError(xstring::format("Meta-data: wrong `%s' type, must be %s",name,BeNode::TypeName(type)));
      return 0;
   }
   return node;
}

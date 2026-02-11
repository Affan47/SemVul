set_print(node,keyw,attrw,prec_parent)
struct treenode *node;
char *keyw,*attrw;
int prec_parent;
{ struct treenode *nnode;
  sprintf(pos,"%s ",keyw);
  pos += strlen(pos);
  nnode = node + node->left;
  if ( nnode->type == WHERE_ ) nnode += nnode->left;
  exprint_recur(nnode,prec_parent);
  sprintf(pos," %s ",attrw);
  pos += strlen(pos);
  if ( node->right )  exprint_recur(node+node->right,prec_parent);
  if ( node[node->left].type == WHERE_ )
  { node+= node->left;
    sprintf(pos," where "); pos += strlen(pos);
    exprint_recur(node+node->right,prec_parent);
  }
  return;
}

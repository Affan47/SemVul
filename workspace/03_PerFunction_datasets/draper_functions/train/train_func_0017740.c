append_node(char * orig, BtRbNode *pNode, int indent)
{
  char buf[128];
  int i;

  for( i=0; i<indent; i++ ){
      orig = append_val(orig, " ");
  }

  sprintf(buf, "%p", pNode);
  orig = append_val(orig, buf);

  if( pNode ){
    indent += 3;
    if( pNode->isBlack ){
      orig = append_val(orig, " B \n");
    }else{
      orig = append_val(orig, " R \n");
    }
    orig = append_node( orig, pNode->pLeft, indent );
    orig = append_node( orig, pNode->pRight, indent );
  }else{
    orig = append_val(orig, "\n");
  }
  return orig;
}

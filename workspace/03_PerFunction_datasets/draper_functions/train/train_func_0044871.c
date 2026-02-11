attributeValue(ParsedMarkup *p, int attrId){
  int i;
  for(i=0; i<p->nAttr; i++){
    if( p->aAttr[i].iACode==attrId ){
      return p->aAttr[i].zValue;
    }
  }
  return 0;
}

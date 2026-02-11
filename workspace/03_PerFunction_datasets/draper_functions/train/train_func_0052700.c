removeAttr(int aid, const char* attrval) {
  if (this->attrs==NULL || aid<0) return 0;
  int delcount=0;
  for (int i=0;i<this->attrs->Count();i++) {
     if (aid==this->attrs->Get(i)->attr_id) {
       if (attrval==NULL ||
          strcmp(attrval, this->attrs->Get(i)->attr_val)==0) {
             delcount++;
             this->attrs->freeItem(i);
             }
       }
     }
  if (delcount>0) this->attrs->Pack();
  return delcount;
}

GACLreturnEntry(GRSTgaclAcl *acl, int entry_no){

  int number;
  GRSTgaclEntry *entry;

  if (acl==NULL) return NULL;

  entry=acl->firstentry;
  number=1;

  while (entry!=NULL)
  {
    if (number==entry_no) return entry;
    number++;
    entry=entry->next;
  }

  return NULL;
}

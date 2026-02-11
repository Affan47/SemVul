GRSTgaclAclPrint(GRSTgaclAcl *acl, FILE *fp)
{
  GRSTgaclEntry *entry;

  fputs("<gacl version=\"0.9.0\">\n", fp);

  for (entry = acl->firstentry; entry != NULL; entry = entry->next)
                                            GRSTgaclEntryPrint(entry, fp);

  fputs("</gacl>\n", fp);

  return 1;
}

del_entry_sure(GRSTgaclUser *user, char *dn, GRSTgaclPerm perm, char *help_uri, char *dir_path, char *file, char *dir_uri, char *admin_file){

  GRSTgaclAcl *acl;
  GRSTgaclEntry *entry;
  GRSTgaclCred *cred;
  int entry_no, cred_no, allow, deny, i, timestamp;
  GRSThttpBody bp;

  if (!GRSTgaclPermHasAdmin(perm)) GRSThttpError ("403 Forbidden");

  acl = GRSTgaclAclLoadFile(GRSTgaclFileFindAclname(dir_path));

  if (acl==NULL){
    GRSThttpError ("500 Unable to read from ACL file");
    return;
  }


  entry_no=atol(GRSThttpGetCGI("entry_no"));
  entry = GACLreturnEntry(acl, entry_no);
  if(entry==NULL || entry_no<1 || entry_no>GACLentriesInAcl(acl) ){
    GRSThttpError ("500 Unable to read from ACL file");
    return;
  }

  StartHTML(&bp, dir_uri, dir_path);
  GRSThttpPrintf (&bp, "<h1 align=center>Do you really want to delete the following entry?</h1><br><br>\n");
  GRSThttpPrintf (&bp,"<br>Entry %d:<br>\n", entry_no);


  cred=entry->firstcred;
  cred_no=1;

  GRSTgaclCredTableStart(&bp);
  while (cred!=NULL){

    GRSTgaclCredTableAdd(user, entry, cred, cred_no, entry_no, 0, 0, &bp, dn, perm, help_uri, dir_path, file, dir_uri, admin_file);

    cred=cred->next;
    cred_no++;
  }

  GRSTgaclCredTableEnd (entry, entry_no, 0, 0, &bp, dn, perm, help_uri, dir_path, file, dir_uri, admin_file);

  StartForm(&bp, dir_uri, dir_path, admin_file, atol(GRSThttpGetCGI("timestamp")), "del_entry");
  GRSThttpPrintf (&bp, "<input type=\"hidden\" name=\"entry_no\" value=\"%d\">\n", entry_no);
  GRSThttpPrintf (&bp, " <p align=center><input type=\"submit\" value=\"Yes\" name=\"B1\"></p>\n</form>\n");

  admin_continue(dn, perm, help_uri, dir_path, file, dir_uri, admin_file, &bp);
  return;
}

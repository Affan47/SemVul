readBoolDescriptor(VimosDescriptor *vDesc, const char *name,
                             VimosBool *val, char *comment)
{
  VimosDescriptor *desc;
  char  modName[] = "readBoolDescriptor";


  desc = findDescriptor(vDesc, name);


  if (desc == NULL) {
    *val = VM_FALSE;

    if (comment)
      strcpy(comment, "");

    cpl_msg_debug(modName, "Cannot find descriptor %s", name);
    return(VM_FALSE);
  }


  if (desc->descType != VM_BOOL) {
    *val = VM_FALSE;

    if (comment)
      strcpy(comment, "");

    cpl_msg_debug(modName, "Descriptor %s is not boolean", name);
    return(VM_FALSE);
  }


  *val = desc->descValue->b;

  if (comment)
    strcpy(comment, desc->descComment);

  return(VM_TRUE);

}

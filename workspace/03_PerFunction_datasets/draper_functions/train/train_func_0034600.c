newLineCatalog()
{
  VimosTable *newTab;


  newTab = newTable();


  if (newTab == NULL) {
    cpl_msg_error("newLineCatalog","The function newTable has returned NULL");
    return(NULL);
  }


  strcpy(newTab->name, VM_LIN);
  newTab->descs = newStringDescriptor("ESO PRO TABLE", VM_LIN, "");
  if (newTab->descs == NULL) {

    pil_free(newTab);
    cpl_msg_error("newLineCatalog","The function newStringDescriptor has returned NULL");
    return(NULL);
  }


  return(newTab);

}

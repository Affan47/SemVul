newAdfSlitHolder()
{
  const char modName[] = "newAdfSlitHolder";
  VimosAdfSlitHolder *slitHolder;

  slitHolder = (VimosAdfSlitHolder *) pil_malloc(sizeof(VimosAdfSlitHolder));

  if (slitHolder == NULL) {
    cpl_msg_error(modName, "Allocation Error");
    return(NULL);
  }
  slitHolder->slitType = VM_ADF_UNDF_SLIT;

  slitHolder->slit = NULL;
  slitHolder->prev = NULL;
  slitHolder->next = NULL;

  return(slitHolder);

}

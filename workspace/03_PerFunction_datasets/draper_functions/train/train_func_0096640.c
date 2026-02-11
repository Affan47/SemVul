_Destroy_GCIO (
                                         GCExportFileH** hGXT,
                                         int delFile
                                       )
{
  if( delFile && GetGCMode_GCIO(*hGXT)==vWriteAccess_GCIO )
  {
    VSIFClose(GetGCHandle_GCIO(*hGXT));
    SetGCHandle_GCIO(*hGXT, NULL);
    VSIUnlink(CPLFormFilename(GetGCPath_GCIO(*hGXT),GetGCBasename_GCIO(*hGXT),GetGCExtension_GCIO(*hGXT)));
  }
  _ReInit_GCIO(*hGXT);
  CPLFree(*hGXT);
  *hGXT= NULL;
}

_ReInit_GCIO (
                                        GCExportFileH* hGXT
                                      )
{
  if( GetGCMeta_GCIO(hGXT) )
  {
    DestroyHeader_GCIO(&(GetGCMeta_GCIO(hGXT)));
  }
  if( GetGCHandle_GCIO(hGXT) )
  {
    VSIFClose(GetGCHandle_GCIO(hGXT));
  }
  if( GetGCExtension_GCIO(hGXT) )
  {
    CPLFree(GetGCExtension_GCIO(hGXT));
  }
  if( GetGCBasename_GCIO(hGXT) )
  {
    CPLFree(GetGCBasename_GCIO(hGXT));
  }
  if( GetGCPath_GCIO(hGXT) )
  {
    CPLFree(GetGCPath_GCIO(hGXT));
  }
  SetGCCache_GCIO(hGXT,"");
  _Init_GCIO(hGXT);
}

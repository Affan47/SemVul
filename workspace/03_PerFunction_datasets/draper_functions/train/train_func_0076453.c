GetSize(unsigned long tprop_cache_id,
                                  int font_size,
                                  FT_Size *size)
{
#if VTK_FTFC_DEBUG_CD
  printf("vtkFreeTypeUtilities::GetSize()\n");
#endif

  if (!size || font_size <= 0)
    {
    vtkErrorMacro(<< "Wrong parameters, size is NULL or invalid font size");
    return 0;
    }

#ifdef VTK_FREETYPE_CACHING_SUPPORTED
  FTC_Manager *manager = this->GetCacheManager();
  if (!manager)
    {
    vtkErrorMacro(<< "Failed querying the cache manager !");
    return 0;
    }


  FTC_FaceID face_id = reinterpret_cast<FTC_FaceID>(tprop_cache_id);

  FTC_ScalerRec scaler_rec;
  scaler_rec.face_id = face_id;
  scaler_rec.width = font_size;
  scaler_rec.height = font_size;
  scaler_rec.pixel = 1;

  FT_Error error = FTC_Manager_LookupSize(*manager, &scaler_rec, size);
  if (error)
    {
    vtkErrorMacro(<< "Failed looking up a FreeType Size");
    }

  return error ? 0 : 1;
#else
  (void)tprop_cache_id;
  vtkErrorMacro("GetSize only supported in FreeType 2.1.9 or higher. "
    "Current version " << FREETYPE_MAJOR << "." << FREETYPE_MINOR
    << "." << FREETYPE_PATCH);
  return 0;
#endif
}

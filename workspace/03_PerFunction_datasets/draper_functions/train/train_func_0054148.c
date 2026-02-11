CanReadFile(const char *file)
{

  std::string filename = file;

  if ( filename == "" )
    {
    itkDebugMacro(<< "No filename specified.");
    return false;
    }


  PNGFileWrapper pngfp(file, "rb");
  if ( pngfp.m_FilePointer == ITK_NULLPTR )
    {
    return false;
    }
  unsigned char header[8];
  size_t temp = fread(header, 1, 8, pngfp.m_FilePointer);
  if( temp != 8 )
    {
    itkExceptionMacro( "PNGImageIO failed to read header for file: "
      << this->GetFileName() << std::endl
      << "Reason: fread read only " << temp
      << " instead of 8" );
    }
  bool is_png = !png_sig_cmp(header, 0, 8);
  if ( !is_png )
    {
    return false;
    }
  png_structp png_ptr = png_create_read_struct
                          (PNG_LIBPNG_VER_STRING, (png_voidp)ITK_NULLPTR,
                          ITK_NULLPTR, ITK_NULLPTR);
  if ( !png_ptr )
    {
    return false;
    }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if ( !info_ptr )
    {
    png_destroy_read_struct(&png_ptr,
                            (png_infopp)ITK_NULLPTR, (png_infopp)ITK_NULLPTR);
    return false;
    }

  png_infop end_info = png_create_info_struct(png_ptr);
  if ( !end_info )
    {
    png_destroy_read_struct(&png_ptr, &info_ptr,
                            (png_infopp)ITK_NULLPTR);
    return false;
    }
  png_destroy_read_struct(&png_ptr, &info_ptr,
                          &end_info);

  return true;
}

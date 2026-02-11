OpenWriter()
{
  if (m_WriterOpen)
    {
    itkExceptionMacro("Cannot open writer while video is already open for writing");
    }

  if (m_ReaderOpen)
    {
    itkExceptionMacro("Cannot open writer while video is already open for reading");
    }


  if (m_FileNames.size() == 0)
    {
    itkExceptionMacro("Cannot open reader without file names set");
    }


  m_ImageIO = ImageIOFactory::CreateImageIO(
      m_FileNames[0].c_str(), ImageIOFactory::WriteMode);
  if (!m_ImageIO.IsNull() )
    {
    m_WriterOpen = true;
    }
  else
    {
    itkExceptionMacro("File failed to open for writing");
    }
}

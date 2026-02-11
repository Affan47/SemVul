OpenStream(std::ofstream & outputStream, bool binary)
{
  std::ios::openmode mode(std::ios::out);

  if ( binary )
    {
    mode |= std::ios::binary;
    }
  if ( this->m_AppendMode )
    {
    mode |= std::ios::app;
    }

  outputStream.open(m_FileName.c_str(), mode);

  if ( outputStream.fail() )
    {
    outputStream.close();
    itkExceptionMacro("Failed opening file" << m_FileName);
    }
}

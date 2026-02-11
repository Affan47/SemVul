GetFile() const
{

  return m_ExceptionData.IsNull() ? "" : this->GetExceptionData()->m_File.c_str();
}

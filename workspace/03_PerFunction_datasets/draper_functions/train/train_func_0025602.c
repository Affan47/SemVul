getDocumentOLEStream(const char *const name)
{
  using boost::filesystem::path;

  const path filePath = m_path / name;

  return is_regular_file(filePath) ? new WPXFileStream(filePath.string().c_str()) : 0;
}

getCompressionCmds(const std::string & filepath, std::string & compressionCmd,
                                     std::string & decompressionCmd,
                                     std::string & compressionSuffix)
{

  compressionCmd = kCatCommand;
  decompressionCmd = kCatCommand;
  if (filepath.length() > kGzipped.size() &&
      filepath.find(kGzipped) == filepath.length()
      - kGzipped.length()) {
    compressionCmd = kGzipCommand;
    decompressionCmd = kGunzipCommand;
    compressionSuffix = kGzipped;
  } else if (filepath.length() > kBzipped2.size() &&
             filepath.find(kBzipped2) == filepath.length()
             - kBzipped2.length() ) {
    compressionCmd = kBzip2Command;
    decompressionCmd = kBunzip2Command;
    compressionSuffix = kBzipped2;;
  }
  return (compressionCmd != kCatCommand && decompressionCmd != kCatCommand);
}

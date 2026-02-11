Write(const std::string& filename,
                        uint32_t width, uint32_t height, TTDataType dataType,
                        const std::vector<uint32_t>& data) {
  if (!VerifyVector(width, height, dataType, data))
    throw ttiff_error("Data vector too small");

  std::ofstream file;
  file.open(filename.c_str(), std::ios::binary);
  if (file.bad()) throw ttiff_error("Unable to open file");
  WriteHeader(file);
  WriteIDF(file, width, height, 4, dataType, false);
  WriteData(file, width, height, dataType, data);
}

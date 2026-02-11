EncodeFile(std::string file)
{
  std::string tarFile = file + "_temp.tar.gz";
  std::vector<cmStdString> files;
  files.push_back(file);

  if(!cmSystemTools::CreateTar(tarFile.c_str(), files, true, false, false))
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Error creating tar while "
      "attaching file: " << file << std::endl);
    return "";
    }
  long len = cmSystemTools::FileLength(tarFile.c_str());
  std::ifstream ifs(tarFile.c_str(), std::ios::in
#ifdef _WIN32
    | std::ios::binary
#endif
    );
  unsigned char *file_buffer = new unsigned char [ len + 1 ];
  ifs.read(reinterpret_cast<char*>(file_buffer), len);
  ifs.close();
  cmSystemTools::RemoveFile(tarFile.c_str());

  unsigned char *encoded_buffer
    = new unsigned char [ static_cast<int>(len * 1.5 + 5) ];

  unsigned long rlen
    = cmsysBase64_Encode(file_buffer, len, encoded_buffer, 1);

  std::string base64 = "";
  for(unsigned long i = 0; i < rlen; i++)
    {
    base64 += encoded_buffer[i];
    }
  delete [] file_buffer;
  delete [] encoded_buffer;

  return base64;
}

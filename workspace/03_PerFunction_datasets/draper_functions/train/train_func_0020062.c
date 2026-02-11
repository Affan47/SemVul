Finalize()
{
  char md5out[32];
  cmsysMD5_FinalizeHex(this->MD5, md5out);
  return std::string(md5out, 32);
}

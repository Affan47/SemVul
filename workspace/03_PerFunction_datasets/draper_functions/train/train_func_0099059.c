GetHashForFile(std::string filename) const
{
   std::string fileHash;

   FileFd Fd(filename, FileFd::ReadOnly);
   if(Type == "MD5Sum")
   {
      MD5Summation MD5;
      MD5.AddFD(Fd);
      fileHash = (std::string)MD5.Result();
   }
   else if (Type == "SHA1")
   {
      SHA1Summation SHA1;
      SHA1.AddFD(Fd);
      fileHash = (std::string)SHA1.Result();
   }
   else if (Type == "SHA256")
   {
      SHA256Summation SHA256;
      SHA256.AddFD(Fd);
      fileHash = (std::string)SHA256.Result();
   }
   else if (Type == "SHA512")
   {
      SHA512Summation SHA512;
      SHA512.AddFD(Fd);
      fileHash = (std::string)SHA512.Result();
   }
   Fd.Close();

   return fileHash;
}

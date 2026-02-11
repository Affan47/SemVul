open(const char *file_name)
{
   FileInputStream *in;

   this->close();

   in = new FileInputStream;
   if (!in->open(file_name) || !this->open(in))
   {
      delete in;
      return false;
   }

   return true;
}

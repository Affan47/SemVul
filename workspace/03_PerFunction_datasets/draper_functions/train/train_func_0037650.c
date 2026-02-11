GrabFirst(string Path,string &To,unsigned int Depth)
{
   string::size_type I = 0;
   do
   {
      I = Path.find('/',I+1);
      Depth--;
   }
   while (I != string::npos && Depth != 0);

   if (I == string::npos)
      return false;

   To = string(Path,0,I+1);
   return true;
}

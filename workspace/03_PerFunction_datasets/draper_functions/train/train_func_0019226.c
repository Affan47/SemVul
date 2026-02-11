ReadLine(std::string &Text)
{
   if (Process == -1 || ReadFd == -1)
      return false;


   while (Len < sizeof(Buffer))
   {

      for (unsigned int I = 0; I != Len; I++)
      {

         if (Buffer[I] == 0)
            Buffer[I] = '?';


         if (Buffer[I] != '\n')
            continue;

         I++;
         Text = std::string(Buffer,I);
         memmove(Buffer,Buffer+I,Len - I);
         Len -= I;
         return true;
      }


      if (WaitFd(ReadFd,false,TimeOut) == false)
      {
         Close();
         return _error->Error(_("Connection timeout"));
      }


      int Res = read(ReadFd,Buffer + Len,sizeof(Buffer) - Len);
      if (Res <= 0)
      {
         _error->Errno("read",_("Read error"));
         Close();
         return false;
      }
      Len += Res;
   }

   return _error->Error(_("A response overflowed the buffer."));
}

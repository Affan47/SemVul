find_position(int n)
{


   if (m_file == NULL)
   {

      return;
   }


   if (n == 0)
   {


      fseek(m_file, 0, SEEK_END);
      return;
   }

   const int bufSize (2048);

   char buf[bufSize];


   int bytesToRead = bufSize;


   long pos = 0;


   fseek(m_file, 0, SEEK_END);


   pos = ftell(m_file);

   while (pos != 0)
   {

      pos -= (bufSize-1);


      if (pos < 0)
      {


	 bytesToRead += pos;


	 pos = 0;
      }


      fseek(m_file, pos, SEEK_SET);


      for (int j = 0 ; j < bytesToRead-1 ; j++)
      {
	 buf[j] = fgetc(m_file);
      }

      buf[bytesToRead-1] = '\0';


      for (int i = bytesToRead-1 ; i >= 0 ; i--)
      {

	 if (buf[i] == '\n')
	 {


	    n--;

	    if (n < 0)
	    {

	       fseek(m_file, pos + i + 1, SEEK_SET);
	       return;
	    }
	 }
      }
   }


   fseek(m_file, 0, SEEK_SET);
}

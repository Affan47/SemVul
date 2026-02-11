Scan(const char *Start,unsigned long MaxLength)
{
   const char *End = Start + MaxLength;
   Stop = Section = Start;
   memset(AlphaIndexes,0,sizeof(AlphaIndexes));

   if (Stop == 0)
      return false;

   TagCount = 0;
   while (TagCount+1 < sizeof(Indexes)/sizeof(Indexes[0]) && Stop < End)
   {
      TrimRecord(true,End);


      if(Stop == End)
         return true;


      if (isspace(Stop[0]) == 0)
      {
	 Indexes[TagCount++] = Stop - Section;
	 AlphaIndexes[AlphaHash(Stop,End)] = TagCount;
      }

      Stop = (const char *)memchr(Stop,'\n',End - Stop);

      if (Stop == 0)
	 return false;

      for (; Stop+1 < End && Stop[1] == '\r'; Stop++)

         ;


      if (Stop+1 < End && Stop[1] == '\n')
      {
	 Indexes[TagCount] = Stop - Section;
	 TrimRecord(false,End);
	 return true;
      }

      Stop++;
   }

   return false;
}

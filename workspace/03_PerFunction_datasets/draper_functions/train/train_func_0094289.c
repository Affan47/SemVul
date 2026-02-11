DropBinaryArch(vector<string> &List)
{

   for (unsigned int I = 0; I < List.size(); I++)
   {
      const char *Str = List[I].c_str();
      const char *Start, *End;
      if ((Start = strstr(Str,"/binary-")) == 0)
	 continue;


      Start += 8;
      if ((End = strstr(Start,"/")) != 0 && Start != End &&
          APT::Configuration::checkArchitecture(string(Start, End)) == true)
	 continue;


      List.erase(List.begin() + I);
      --I;
   }

   return true;
}

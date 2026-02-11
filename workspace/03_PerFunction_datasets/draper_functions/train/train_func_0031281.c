Add(GenContents &Contents,std::string const &Package)
{
   const char *Start = Data;
   char *Pkg = Contents.Mystrdup(Package.c_str());
   for (const char *I = Data; I < Data + CurSize; I++)
   {
      if (*I == 0)
      {
	 Contents.Add(Start,Pkg);
	 Start = ++I;
      }
   }
}

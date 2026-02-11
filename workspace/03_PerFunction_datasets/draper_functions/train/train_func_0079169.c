Score(Configuration const &Cnf)
{
   if (Cnf.Find("edsp::scenario", "") == "stdin")
      return 1000;
   if (RealFileExists(Cnf.FindFile("edsp::scenario","")) == true)
      return 1000;
   return -1000;
}

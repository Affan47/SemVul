Describe(bool Short) const
{
   char S[300];
   if (Short == true)
      snprintf(S,sizeof(S),"%s",Info("Sources").c_str());
   else
      snprintf(S,sizeof(S),"%s (%s)",Info("Sources").c_str(),
	       IndexFile("Sources").c_str());

   return S;
}

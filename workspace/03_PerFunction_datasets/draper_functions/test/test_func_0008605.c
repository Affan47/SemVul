DispatchArg(Dispatch *Map,bool NoMatch)
{
   int I;
   for (I = 0; Map[I].Match != 0; I++)
   {
      if (strcmp(FileList[0],Map[I].Match) == 0)
      {
	 bool Res = Map[I].Handler(*this);
	 if (Res == false && _error->PendingError() == false)
	    _error->Error("Handler silently failed");
	 return Res;
      }
   }


   if (Map[I].Match == 0)
   {
      if (NoMatch == true)
	 _error->Error(_("Invalid operation %s"),FileList[0]);
   }

   return false;
}

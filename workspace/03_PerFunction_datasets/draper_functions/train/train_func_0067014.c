FindB(const char *Name,bool const &Default) const
{
   const Item *Itm = Lookup(Name);
   if (Itm == 0 || Itm->Value.empty() == true)
      return Default;

   return StringToBool(Itm->Value,Default);
}

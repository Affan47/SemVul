CndSet(const char *Name,const string &Value)
{
   Item *Itm = Lookup(Name,true);
   if (Itm == 0)
      return;
   if (Itm->Value.empty() == true)
      Itm->Value = Value;
}

selected_chainsetup(void) const
{
 if (selected_chainsetup_repp != 0)
   return selected_chainsetup_repp->name();

 return "";
}

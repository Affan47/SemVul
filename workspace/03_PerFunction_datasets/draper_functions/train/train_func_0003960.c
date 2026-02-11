optionsModel(MSStringVector& options_)
{
  if (optionMenu()!=0) optionMenu()->model(options_);
  else
   {
     _optionMenu=new MSOptionPopupMenu(this,options_);
     optionMenu()->columns(columns());
   }
}

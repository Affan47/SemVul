accuracy()
{
 if (!is_gun())
  return 0;
 it_gun* gun = dynamic_cast<it_gun*>(type);
 int ret = gun->accuracy;
 for (int i = 0; i < contents.size(); i++) {
  if (contents[i].is_gunmod())
   ret -= (dynamic_cast<it_gunmod*>(contents[i].type))->accuracy;
 }
 ret += damage * 2;
 return ret;
}

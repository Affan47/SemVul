charges_of(itype_id it)
{
 int count = 0;
 for (int i = 0; i < items.size(); i++) {
  for (int j = 0; j < items[i].size(); j++) {
   if (items[i][j].type->id == it) {
    if (items[i][j].charges < 0)
     count++;
    else
     count += items[i][j].charges;
   }
   for (int k = 0; k < items[i][j].contents.size(); k++) {
    if (items[i][j].contents[k].type->id == it) {
     if (items[i][j].contents[k].charges < 0)
      count++;
     else
      count += items[i][j].contents[k].charges;
    }
   }
  }
 }
 return count;
}

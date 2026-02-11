item_by_letter(char ch)
{
 for (int i = 0; i < items.size(); i++) {
  if (items[i][0].invlet == ch)
   return items[i][0];
 }
 return nullitem;
}

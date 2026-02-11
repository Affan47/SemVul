add_item(item newit)
{
 for (int i = 0; i < items.size(); i++) {
  if (items[i][0].stacks_with(newit)) {
   newit.invlet = items[i][0].invlet;
   items[i].push_back(newit);
   return;
  }
 }
 if (!newit.invlet_is_okay() || index_by_letter(newit.invlet) != -1) {
  int ch;
  for (ch = 'a'; ch <= 'z' && ch > 0; ch++) {
   if (index_by_letter(ch) == -1) {
    newit.invlet = ch;
    ch = -1;
   }
  }
  if (ch > 0) {
   for (ch = 'A'; ch <= 'Z' && ch > 0; ch++) {
    if (index_by_letter(ch) == -1) {
     newit.invlet = ch;
     ch = -1;
    }
   }
  }
  if (ch > 0)
   newit.invlet = '`';
 }
 std::vector<item> newstack;
 newstack.push_back(newit);
 items.push_back(newstack);
}

use_amount(itype_id it, int quantity, bool use_container)
{
 for (int i = 0; i < items.size() && quantity > 0; i++) {
  for (int j = 0; j < items[i].size() && quantity > 0; j++) {

   bool used_item_contents = false;
   for (int k = 0; k < items[i][j].contents.size() && quantity > 0; k++) {
    if (items[i][j].contents[k].type->id == it) {
     quantity--;
     items[i][j].contents.erase(items[i][j].contents.begin() + k);
     k--;
     used_item_contents = true;
    }
   }

   if (use_container && used_item_contents) {
    items[i].erase(items[i].begin() + j);
    j--;
    if (items[i].empty()) {
     items.erase(items.begin() + i);
     i--;
     j = 0;
    }
   } else if (items[i][j].type->id == it && quantity > 0) {
    quantity--;
    items[i].erase(items[i].begin() + j);
    j--;
    if (items[i].empty()) {
     items.erase(items.begin() + i);
     i--;
     j = 0;
    }
   }
  }
 }
}

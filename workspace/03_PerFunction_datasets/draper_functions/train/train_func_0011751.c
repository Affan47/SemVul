last()
{
   if (num_items == 0) {
      return NULL;
   } else {
      cur_item = num_items;
      return items[num_items-1];
   }
}

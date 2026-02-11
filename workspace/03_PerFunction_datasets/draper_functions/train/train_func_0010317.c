_item_process(Elm_Genlist_Smart_Data *sd,
              Elm_Gen_Item *it)
{
   if (!_item_block_add(sd, it)) return 1;
   if (!sd->blocks)
     _item_block_realize(it->item->block);

   return 0;
}

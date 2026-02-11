_evry_item_sel(Evry_State *s, Evry_Item *it)
{
   if (s->cur_item == it) return;

   _evry_item_desel(s);

   evry_item_ref(it);
   it->selected = EINA_TRUE;

   s->cur_item = it;
}

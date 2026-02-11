_ibar_free(IBar *b)
{
   _ibar_empty(b);
   evas_object_del(b->o_box);
   if (b->o_drop) evas_object_del(b->o_drop);
   if (b->o_drop_over) evas_object_del(b->o_drop_over);
   if (b->o_empty) evas_object_del(b->o_empty);
   _ibar_order_del(b);
   E_FREE(b);
   ibars = eina_list_remove(ibars, b);
}

_decorate_all_item_position(Elm_Gen_Item *it,
                            int itx,
                            int ity)
{
   if ((!it) || (!GL_IT(it)->wsd->decorate_all_mode)) return;
   evas_object_resize(it->deco_all_view, it->item->w, it->item->h);
   evas_object_move(it->deco_all_view, itx, ity);
}

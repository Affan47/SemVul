_evas_textblock_range_calc_x_w(const Evas_Object_Textblock_Item *it,
      Evas_Coord *x, Evas_Coord *w, Eina_Bool start, Eina_Bool switch_items)
{
   if ((start && !switch_items) || (!start && switch_items))
     {
#ifdef BIDI_SUPPORT
        if (((it->type == EVAS_TEXTBLOCK_ITEM_TEXT) &&
            _ITEM_TEXT(it)->text_props.bidi.dir == EVAS_BIDI_DIRECTION_RTL)
            ||
            ((it->type == EVAS_TEXTBLOCK_ITEM_FORMAT) &&
             _ITEM_FORMAT(it)->bidi_dir == EVAS_BIDI_DIRECTION_RTL))
          {
             *w = *x + *w;
             *x = 0;
          }
        else
#endif
          {
             *w = it->adv - *x;
          }
     }
   else
     {
#ifdef BIDI_SUPPORT
        if (((it->type == EVAS_TEXTBLOCK_ITEM_TEXT) &&
            _ITEM_TEXT(it)->text_props.bidi.dir == EVAS_BIDI_DIRECTION_RTL)
            ||
            ((it->type == EVAS_TEXTBLOCK_ITEM_FORMAT) &&
             _ITEM_FORMAT(it)->bidi_dir == EVAS_BIDI_DIRECTION_RTL))
          {
             *x = *x + *w;
             *w = it->adv - *x;
          }
        else
#endif
          {
             *w = *x;
             *x = 0;
          }
     }

}

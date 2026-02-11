clickgame_animate_item(FishItem *fishitem)
{
  gint currentItem;


  currentItem = fishitem->currentItem;
  fishitem->currentItem++;
  if(fishitem->currentItem >= g_slist_length(fishitem->cur_frames))
    fishitem->currentItem=0;

  g_object_set((GooCanvasItem *)g_slist_nth_data(fishitem->cur_frames,
						 fishitem->currentItem),
	       "visibility", GOO_CANVAS_ITEM_VISIBLE,
		NULL);

  g_object_set((GooCanvasItem *)g_slist_nth_data(fishitem->cur_frames,
						 currentItem),
	       "visibility", GOO_CANVAS_ITEM_INVISIBLE,
	       NULL);
}

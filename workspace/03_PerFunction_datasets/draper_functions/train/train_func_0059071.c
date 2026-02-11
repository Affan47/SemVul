clickgame_next_level()
{
  static  gchar *bglist[] =
    {
      "clickgame/sea1.jpg",
      "clickgame/sea2.jpg",
      "clickgame/sea3.jpg",
      "clickgame/sea4.jpg",
      "clickgame/sea5.jpg",
      "clickgame/sea6.jpg"
    };

  int bgx = gcomprisBoard->level - 1;

  if (bgx < 0 || G_N_ELEMENTS(bglist) <= bgx)
    bgx = G_N_ELEMENTS(bglist) - 1;

  gc_set_background(goo_canvas_get_root_item(gcomprisBoard->canvas),
		    bglist[bgx]);

  gc_bar_set_level(gcomprisBoard);


  moveSpeed=100+(40/(gcomprisBoard->level));
  fallSpeed=5000-gcomprisBoard->level*200;
  imageZoom =
    0.75 + 0.25
    * ((double)(gcomprisBoard->maxlevel - gcomprisBoard->level + 1)
       / gcomprisBoard->maxlevel);
  gcomprisBoard->sublevel=0;
  gc_score_set(gcomprisBoard->sublevel);

  while (g_list_length (item_list) < 3) {
    FishItem *fish = clickgame_create_item();
    if (!fish) break;
    goo_canvas_item_translate(fish->rootitem,
                          fish->speed * (rand() % 200), 0.0);
  }
}

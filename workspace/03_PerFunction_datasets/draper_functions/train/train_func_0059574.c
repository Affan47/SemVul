clockgame_next_level()
{

  gc_bar_set_level(gcomprisBoard);
  gc_score_set(gcomprisBoard->sublevel);

  destroy_all_items();


  get_random_hour(&timeToFind);


  do {
    get_random_hour(&currentTime);
  } while(time_equal(&timeToFind, &currentTime));

  clockgame_create_item(goo_canvas_get_root_item(gcomprisBoard->canvas));

}

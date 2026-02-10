player_win(LettersItem *item)
{

  gc_sound_play_ogg ("sounds/flip.wav", NULL);

  g_assert(gcomprisBoard!=NULL);

  gcomprisBoard->sublevel++;
  gc_score_set(gcomprisBoard->sublevel);

  g_ptr_array_remove(items,item);
  g_ptr_array_add(items2del,item);

  g_object_set (item->rootitem, "visibility", GOO_CANVAS_ITEM_INVISIBLE, NULL);
  g_timeout_add (500,(GSourceFunc) wordsgame_delete_items, NULL);

  if(gcomprisBoard->sublevel > gcomprisBoard->number_of_sublevel)
    {


      gc_bonus_display(TRUE, GC_BONUS_LION);
      drop_items_id = g_timeout_add (3000,
				       (GSourceFunc) wordsgame_drop_items, NULL);


      gcomprisBoard->level++;
      gcomprisBoard->sublevel = 1;
      if(gcomprisBoard->level>gcomprisBoard->maxlevel)
	gcomprisBoard->level = gcomprisBoard->maxlevel;

      wordsgame_next_level_unlocked();
    }
  else
    {


      if(items->len==0)
        {
	  if ((fallSpeed-=INCREMENT_FALLSPEED) < MIN_FALLSPEED) fallSpeed+=INCREMENT_FALLSPEED;
	  if ((speed-=INCREMENT_SPEED) < MIN_SPEED) speed+=INCREMENT_SPEED;

          if (drop_items_id) {

            g_source_remove (drop_items_id);
            drop_items_id = 0;
          }

          if(!drop_items_id) {
            drop_items_id = g_timeout_add (0,
					   (GSourceFunc) wordsgame_drop_items,
					   NULL);
          }

        }
    }

}

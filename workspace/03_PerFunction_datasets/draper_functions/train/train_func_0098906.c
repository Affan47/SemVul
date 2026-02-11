reversecount_next_level()
{

  gc_set_background(goo_canvas_get_root_item(gcomprisBoard->canvas),
		    imageList[gcomprisBoard->level-1]);

  reversecount_destroy_all_items();
  gamewon = FALSE;


  switch(gcomprisBoard->level)
    {
    case 1:
      number_of_item_x = 5;
      number_of_item_y = 5;
      number_of_dices = 1;
      max_dice_number = 3;
      number_of_fish = 3;
      break;
    case 2:
      number_of_item_x = 5;
      number_of_item_y = 5;
      number_of_dices = 1;
      max_dice_number = 6;
      number_of_fish = 6;
      break;
    case 3:
      number_of_item_x = 6;
      number_of_item_y = 6;
      number_of_dices = 1;
      max_dice_number = 9;
      number_of_fish = 6;
      break;
    case 4:
      number_of_item_x = 8;
      number_of_item_y = 6;
      number_of_dices = 1;
      max_dice_number = 3;
      number_of_fish = 6;
      break;
    case 5:
      number_of_item_x = 8;
      number_of_item_y = 6;
      number_of_dices = 2;
      max_dice_number = 6;
      number_of_fish = 10;
      break;
    case 6:
      number_of_item_x = 8;
      number_of_item_y = 8;
      number_of_dices = 2;
      max_dice_number = 9;
      number_of_fish = 10;
      break;
    default:
      number_of_item_x = 10;
      number_of_item_y = 10;
      number_of_dices = 3;
      max_dice_number = 9;
      number_of_fish = 10;
      break;
    }

  animate_speed = ANIMATE_SPEED - gcomprisBoard->level * 60;

  number_of_item = number_of_item_x * 2 + (number_of_item_y - 2) * 2;


  reversecount_create_item(goo_canvas_get_root_item(gcomprisBoard->canvas));

  gc_bar_set_level(gcomprisBoard);

}

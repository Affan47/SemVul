menu_options(MENU *my_menu, WINDOW *win){
    nodelay(win, 0);
    wrefresh(win);
    int c;
    int offset = 0x30;

    while((c = wgetch(win))!= 0x0a){
       switch(c){
   		case KEY_DOWN:
      		menu_driver(my_menu, REQ_DOWN_ITEM);
      		break;
   		case KEY_UP:
       		menu_driver(my_menu, REQ_UP_ITEM);
      		break;
		default:
          if (c> offset && (c <= (my_menu->nitems + offset)))
            return (c-offset) - 1;
          break;
       }
       wrefresh(win);
    }
   return item_index(current_item(my_menu));
}

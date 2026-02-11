set_active( struct widget_menu_entry *menu, const char *path, int active )
{
  if( *path == '/' ) path++;


  menu++;

  for( ; menu->text; menu++ ) {

    const char *p = menu->text, *q = path;


    do {
      if( *p == 9 || *p == 10 ) p++;
    } while( *p && *p++ == *q++ );

    if( *p ) continue;


    if( *q == '/' ) return set_active( menu->submenu, q, active );

    if( *q ) continue;


    menu->inactive = !active;
    return 0;
  }

  return 1;
}

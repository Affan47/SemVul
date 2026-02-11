widget_calculate_option_width(widget_option_entry *menu)
{
  widget_option_entry *ptr;
  int max_width=0;

  if (!menu) {
    return 64;
  }

  max_width = widget_stringwidth( menu->text )+5*8;

  for( ptr = &menu[1]; ptr->text; ptr++ ) {
    int total_width = widget_stringwidth(ptr->text)+3*8;


    if( ptr->suffix ) total_width += widget_stringwidth(ptr->suffix)+4*8;
    if( ptr->options ) {
      int combo_width = 0;
      const char **options = ptr->options;
      while( *options != NULL ) {
        if( combo_width < widget_stringwidth( *options ) )
          combo_width = widget_stringwidth( *options );
        options++;
      }
      total_width += combo_width;
    }

    if (total_width > max_width)
      max_width = total_width;
  }

  return (max_width+options_vert_external_margin*2)/8;
}

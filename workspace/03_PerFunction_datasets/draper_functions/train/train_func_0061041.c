set_activity( gpointer key, gpointer value, gpointer user_data )
{
  periph_type type = GPOINTER_TO_INT( key );
  periph_private_t *private = value;
  int active = 0;
  int *needs_hard_reset = (int *)user_data;

  switch ( private->present ) {
  case PERIPH_PRESENT_NEVER: active = 0; break;
  case PERIPH_PRESENT_OPTIONAL:
    active = private->periph->option ? *(private->periph->option) : 0; break;
  case PERIPH_PRESENT_ALWAYS: active = 1; break;
  }

  *needs_hard_reset =
    ( periph_activate_type( type, active ) && private->periph->hard_reset ) ||
    *needs_hard_reset;
}

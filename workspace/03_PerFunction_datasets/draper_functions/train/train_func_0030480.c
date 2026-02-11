any_click(int buttonId)
{
	if( !has_mouse_event )
      return 0;

   MouseClick* cptr;

   if( buttonId==0 || buttonId==2 )
   {
      cptr = click_buffer+LEFT_BUTTON;

		if( mouse_event_type == LEFT_BUTTON && cptr->count >= 1 )
			return cptr->count;
   }

   if( buttonId==1 || buttonId==2 )
   {
      cptr = click_buffer+RIGHT_BUTTON;

      if( mouse_event_type == RIGHT_BUTTON && cptr->count >= 1 )
         return cptr->count;
   }

	return 0;
}

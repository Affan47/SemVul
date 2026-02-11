user_handler(Gpm_Event *event, void *data)
{
   if (opt_fit) Gpm_FitEvent(event);

   printf("mouse: event 0x%02X, at %2i,%2i (delta %2i,%2i), "
          "buttons %i, modifiers 0x%02X\r\n",
	 event->type,
	 event->x, event->y,
	 event->dx, event->dy,
	 event->buttons, event->modifiers);

   if (event->type & (GPM_DRAG|GPM_DOWN)) {
      if (0 != opt_pointer) {
         GPM_DRAWPOINTER(event);
      }
   }
   return 0;
}

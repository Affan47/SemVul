keystroke(const Event& e)
{
    if (active_) {
   current_window_ = e.window();


   unsigned long keysym = e.keysym();
   for (TE_ViewKeySymInfo* k = &default_key_sym_map[0];
	k->keysym != 0; k++) {
      if (keysym == k->keysym) {
	 TE_ViewKeyFunc f = k->func;
	 (this->*f)();
	 return;
      }
   }


   signed char c;
   if (e.mapkey((char *)&c, 1) == 0)
      return;


#ifndef __sgi
   if (c >= 0) {
#else
   if (1) {
#endif
       TE_ViewKeyFunc f =  key_[c];
       if (f != nil) {
	   (this->*f)();
	   return;
       }
   }

#ifndef __sgi
   if (c >= 0 && (isspace(c) || !iscntrl(c)))
#else
   if (isspace(c) || !iscntrl(c))
#endif
      insert_char(c);
   else
     cerr << "Unknown character - ignored!\n";
}
}

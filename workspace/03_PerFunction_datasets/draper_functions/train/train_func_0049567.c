icalcomponent_vanew (icalcomponent_kind kind, ...)
{
   va_list args;

   icalcomponent *impl = icalcomponent_new_impl(kind);

    if (impl == 0){
	return 0;
    }

   va_start(args,kind);
   icalcomponent_add_children(impl, args);
   va_end(args);

   return impl;
}

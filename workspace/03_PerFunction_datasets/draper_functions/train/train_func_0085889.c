icalcomponent_isa (icalcomponent* component)
{
    struct icalcomponent_impl *impl = (struct icalcomponent_impl *)component;
    icalerror_check_arg_rz( (component!=0), "component");

   if(component != 0)
   {
       return impl->kind;
   }

   return ICAL_NO_COMPONENT;
}

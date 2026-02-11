argval_to_string(argval_t argval)
{
   switch (argval)
   {
   case AV_IGNORE:
      return("ignore");

   case AV_ADD:
      return("add");

   case AV_REMOVE:
      return("remove");

   case AV_FORCE:
      return("force");

   default:
      LOG_FMT(LWARN, "Unknown argval '%d'\n", argval);
      return("");
   }
}

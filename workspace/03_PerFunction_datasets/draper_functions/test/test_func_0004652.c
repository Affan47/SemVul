baculaRegisterEvents(bpContext *ctx, ...)
{
   va_list args;
   uint32_t event;

   va_start(args, ctx);
   while ((event = va_arg(args, uint32_t))) {
      Dmsg1(dbglvl, "dir-Plugin wants event=%u\n", event);
   }
   va_end(args);
   return bRC_OK;
}

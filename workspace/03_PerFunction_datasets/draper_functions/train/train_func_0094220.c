eina_mempool_add(const char *name,
                 const char *context,
                 const char *options,
                 ...)
{
   Eina_Mempool *mp;
   va_list args;

   EINA_SAFETY_ON_NULL_RETURN_VAL(name, NULL);
   DBG("name=%s, context=%s, options=%s",
       name, context ? context : "", options ? options : "");

   va_start(args, options);
   mp = _new_va(name, context, options, args);
   va_end(args);

   DBG("name=%s, context=%s, options=%s, mp=%p",
       name, context ? context : "", options ? options : "", mp);

   return mp;
}

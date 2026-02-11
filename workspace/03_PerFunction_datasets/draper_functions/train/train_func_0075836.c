panic(const char *fmt, ...)
{
   va_list  ap;
   va_start(ap, fmt);

#if defined(HAVE_VSNPRINTF) && defined(HAVE_PROTOTYPE_VSNPRINTF)
   char buf[4096];

#ifdef HAVE_PROTOTYPE_STD__VSNPRINTF
   std::vsnprintf(buf, sizeof(buf), fmt, ap);
#else
   vsnprintf(buf, sizeof(buf), fmt, ap);
#endif


   buf[4095] = '\0';

   DCMQRDB_ERROR("CONFIG Error: " << buf << "!");
#else
   fprintf(stderr, "CONFIG Error: ");
   vfprintf(stderr, fmt, ap);
   fprintf(stderr, "!\n");
#endif
   va_end(ap);
}

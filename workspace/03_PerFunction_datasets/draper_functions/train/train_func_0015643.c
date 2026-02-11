cgi_names(void) const
{
   if(!validurl) const_cast<GURL *>(this)->init();
   GCriticalSectionLock lock((GCriticalSection *) &class_lock);
   return cgi_name_arr;
}

ethsw_debug(ethsw_table_t *t,char *fmt,...)
{
   char module[128];
   va_list ap;

   if (t->debug) {
      va_start(ap,fmt);
      snprintf(module,sizeof(module),"ETHSW %s",t->name);
      m_flog(log_file,module,fmt,ap);
      va_end(ap);
   }
}

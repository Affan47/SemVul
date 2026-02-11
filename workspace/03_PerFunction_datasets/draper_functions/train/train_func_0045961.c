get_version() const
{
   GP<DjVuInfo> info=get_info();
   return info ? info->version : DJVUVERSION;
}

request_data(const DjVuPort * source, const GURL & url)
{
   GCriticalSectionLock lk(&lock);
   GP<DataPool> pool;
   GPosition pos;
   if (map.contains(url, pos))
      pool=map[pos];
   return pool;
}

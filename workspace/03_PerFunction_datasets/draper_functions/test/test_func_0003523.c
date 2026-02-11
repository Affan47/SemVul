appendPath(const GURL &url,
           GMap<GUTF8String,void *> &map,
           GList<GURL> &list)
{
  if( !url.is_empty() && !map.contains(url.get_string()) )
    {
      map[url.get_string()]=0;
      list.append(url);
    }
}

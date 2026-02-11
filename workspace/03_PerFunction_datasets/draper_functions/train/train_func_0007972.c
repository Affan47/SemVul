WalkRewind()
{
  const WordReference&  last                    = WordStat::Last();

  WordKey first_key;


  if(searchKey.Empty()) {
    first_key = last.Key();
  } else {
    prefixKey = searchKey;


    if(prefixKey.PrefixOnly() == NOTOK) {
      prefixKey.Clear();


      first_key = last.Key();
    } else {
      first_key = prefixKey;
    }
  }

  first_key.Pack(key);


  found.Key().CopyFrom(first_key);

  status = OK;
  searchKeyIsSameAsPrefix = searchKey.ExactEqual(prefixKey);
  cursor_get_flags = DB_SET_RANGE;

  return OK;
}

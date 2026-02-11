lookup(CKey const &key)
{
  unsigned long index = make_hash(key);
  if(!db_hashed[index]) return false;


  DB_Bucket *bucket = db_hashed[index];

  if(!bucket->deleted && bucket->record->key == key) {
    linear_index = bucket->index;
    return true;
  }


  bucket = db_hashed[index]->chain;

  while(bucket) {
    if(!bucket->deleted && bucket->record->key == key) {
      linear_index = bucket->index;
      return true;
    }

    bucket = bucket->chain;
  }

  return false;
}

assoc_remove (hash, string)
     HASH_TABLE *hash;
     char *string;
{
  BUCKET_CONTENTS *b;

  b = hash_remove (string, hash, 0);
  if (b)
    {
      free ((char *)b->data);
      free (b->key);
      free (b);
    }
}

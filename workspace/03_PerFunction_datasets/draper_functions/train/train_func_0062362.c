_eet_eina_hash_foreach(void             *hash,
                       Eina_Hash_Foreach cb,
                       void             *fdata)
{
   if (hash)
     eina_hash_foreach(hash, cb, fdata);
}

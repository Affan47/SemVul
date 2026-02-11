___gc_hash_table_ref
   ___P((___SCMOBJ ht,
         ___SCMOBJ key),
        (ht,
         key)
___SCMOBJ ht;
___SCMOBJ key;)
{
  int size2;
  int probe2;
  ___SCMOBJ obj;

  if (!___FIXZEROP(___FIXAND(___FIELD(ht, ___GCHASHTABLE_FLAGS),
                             ___FIX(___GCHASHTABLE_FLAG_KEY_MOVED))))
    ___gc_hash_table_rehash_in_situ (ht);

  size2 = ___INT(___VECTORLENGTH(ht)) - ___GCHASHTABLE_KEY0;
  probe2 = ___GCHASHTABLE_HASH1(key,size2>>1) << 1;
  obj = ___FIELD(ht, probe2+___GCHASHTABLE_KEY0);

  if (___EQP(obj,key))
    return ___FIELD(ht, probe2+___GCHASHTABLE_VAL0);
  else if (!___EQP(obj,___UNUSED))
    {
      int step2 = ___GCHASHTABLE_HASH2(key,size2>>1) << 1;

      for (;;)
        {
          probe2 -= step2;
          if (probe2 < 0)
            probe2 += size2;
          obj = ___FIELD(ht, probe2+___GCHASHTABLE_KEY0);

          if (___EQP(obj,key))
            return ___FIELD(ht, probe2+___GCHASHTABLE_VAL0);
          else if (___EQP(obj,___UNUSED))
            break;
        }
    }

  return ___UNUSED;
}

hash_index(uint32_t key)
{
   hash = key;

   index = ((hash * 1103515249) >> rshift) & mask;
   Dmsg2(dbglvl, "Leave hash_index hash=0x%llx index=%d\n", hash, index);
}

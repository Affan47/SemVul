addValue(const CORBA::ValueBase* val, CORBA::Long current)
{
  OutputTableEntry* e;

  CORBA::ULong hashval = ((omni::ptr_arith_t)val % pd_table_size);

  for (e = pd_table[hashval]; e; e = e->next) {
    if (e->kind == OT_VALUE && e->value == val)
      return e->position;
  }
  e = new OutputTableEntry(val, current, pd_table[hashval]);
  pd_table[hashval] = e;
  return -1;
}

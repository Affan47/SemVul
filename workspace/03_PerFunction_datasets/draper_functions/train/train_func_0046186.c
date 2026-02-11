types_compatible (type *t, type *k)
{

  if (k->key == unsuitable_type)
    return true;

  if (t->key < reference_type || k->key < reference_type)
    return t->key == k->key;


  if (t->key == null_type)
    return k->key != uninitialized_reference_type;
  if (k->key == null_type)
    return t->key != uninitialized_reference_type;


  if (t->klass == NULL)
    return true;
  if (k->klass == NULL)
    verify_fail ("programmer error in type::compatible");


  if (! type_initialized (t) && t->pc == EITHER)
    {


      if (! type_initialized (k) && k->pc != SELF)
	return false;
    }
  else if (type_initialized (t) != type_initialized (k))
    {


      return false;
    }
  else
    {


      if (type_initialized (t))
	{
	  if (t->pc != k->pc && t->pc != UNINIT && k->pc != UNINIT)
	    return false;
	}
    }

  return ref_compatible (t->klass, k->klass);
}

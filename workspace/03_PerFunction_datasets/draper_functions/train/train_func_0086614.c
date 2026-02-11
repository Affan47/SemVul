add_type_assertion (tree klass, int assertion_code, tree op1, tree op2)
{
  htab_t assertions_htab;
  type_assertion as;
  void **as_pp;

  assertions_htab = TYPE_ASSERTIONS (klass);
  if (assertions_htab == NULL)
    {
      assertions_htab = htab_create_ggc (7, type_assertion_hash,
					 type_assertion_eq, NULL);
      TYPE_ASSERTIONS (current_class) = assertions_htab;
    }

  as.assertion_code = assertion_code;
  as.op1 = op1;
  as.op2 = op2;

  as_pp = htab_find_slot (assertions_htab, &as, INSERT);


  if (*as_pp)
    return;

  *as_pp = ggc_alloc_type_assertion ();
  **(type_assertion **)as_pp = as;
}

attributes_s2i(struct v3_ext_method*, struct v3_ext_ctx*, char *data)
{
  int i = 0;

  STACK_OF(AC_ATT_HOLDER) *stack =
    (STACK_OF(AC_ATT_HOLDER) *)data;

  if (data) {
    AC_FULL_ATTRIBUTES *a = AC_FULL_ATTRIBUTES_new();
    sk_AC_ATT_HOLDER_pop_free(a->providers, AC_ATT_HOLDER_free);
    a->providers = sk_AC_ATT_HOLDER_new_null();

    for (i = 0; i < sk_AC_ATT_HOLDER_num(stack); i++)
#if (OPENSSL_VERSION_NUMBER >= 0x10000000L)
      sk_AC_ATT_HOLDER_push(a->providers,
           ASN1_dup_of(AC_ATT_HOLDER, i2d_AC_ATT_HOLDER,
           d2i_AC_ATT_HOLDER,
           sk_AC_ATT_HOLDER_value(stack, i)));
#elif (OPENSSL_VERSION_NUMBER >= 0x0090800fL)
      sk_AC_ATT_HOLDER_push(a->providers,
           (AC_ATT_HOLDER *)ASN1_dup((int (*)(void*, unsigned char**))i2d_AC_ATT_HOLDER,
           (void*(*)(void**, const unsigned char**, long int))d2i_AC_ATT_HOLDER,
           (char *)(sk_AC_ATT_HOLDER_value(stack, i))));
#else
      sk_AC_ATT_HOLDER_push(a->providers,
           (AC_ATT_HOLDER *)ASN1_dup((int (*)())i2d_AC_ATT_HOLDER,
           (char * (*)())d2i_AC_ATT_HOLDER,
           (char *)(sk_AC_ATT_HOLDER_value(stack, i))));
#endif

    return a;
  }
  return NULL;
}

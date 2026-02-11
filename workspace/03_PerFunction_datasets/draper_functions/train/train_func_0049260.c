translate_cc_error(krb5_context context, cc_int32 error)
{
    size_t i;
    krb5_clear_error_message(context);
    for(i = 0; i < sizeof(cc_errors)/sizeof(cc_errors[0]); i++)
	if (cc_errors[i].error == error)
	    return cc_errors[i].ret;
    return KRB5_FCC_INTERNAL;
}

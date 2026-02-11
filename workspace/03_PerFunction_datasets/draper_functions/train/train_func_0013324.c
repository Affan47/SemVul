kt_ops_copy(krb5_context context, const krb5_context src_context)
{
    context->num_kt_types = 0;
    context->kt_types     = NULL;

    if (src_context->num_kt_types == 0)
	return 0;

    context->kt_types = malloc(sizeof(context->kt_types[0]) * src_context->num_kt_types);
    if (context->kt_types == NULL)
	return krb5_enomem(context);

    context->num_kt_types = src_context->num_kt_types;
    memcpy(context->kt_types, src_context->kt_types,
	   sizeof(context->kt_types[0]) * src_context->num_kt_types);

    return 0;
}

krb5_auth_con_add_AuthorizationData(krb5_context context,
				    krb5_auth_context auth_context,
				    int type,
				    krb5_data *data)
{
    AuthorizationDataElement el;

    if (auth_context->auth_data == NULL) {
	auth_context->auth_data = calloc(1, sizeof(*auth_context->auth_data));
	if (auth_context->auth_data == NULL)
	    return krb5_enomem(context);
    }
    el.ad_type = type;
    el.ad_data.data = data->data;
    el.ad_data.length = data->length;

    return add_AuthorizationData(auth_context->auth_data, &el);
}

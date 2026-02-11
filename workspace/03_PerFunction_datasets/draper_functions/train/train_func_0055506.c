get_best_principal(context, plist, client)
    krb5_context context;
    char **plist;
    krb5_principal *client;
{
    krb5_error_code retval =0;
    krb5_principal temp_client, best_client = NULL;

    int i = 0, nelem;

    if (! plist ) return 0;

    nelem = krb5_princ_size(context, *client);

    while(plist[i]){

        if ((retval = krb5_parse_name(context, plist[i], &temp_client))){
            return retval;
        }

        if (data_eq(*krb5_princ_realm(context, *client),
                    *krb5_princ_realm(context, temp_client))) {

            if (nelem &&
                krb5_princ_size(context, *client) > 0 &&
                krb5_princ_size(context, temp_client) > 0) {
                krb5_data *p1 =
                    krb5_princ_component(context, *client, 0);
                krb5_data *p2 =
                    krb5_princ_component(context, temp_client, 0);

                if (data_eq(*p1, *p2)) {

                    if (auth_debug){
                        fprintf(stderr,
                                "get_best_principal: compare with %s\n",
                                plist[i]);
                    }

                    if(best_client){
                        if(krb5_princ_size(context, best_client) >
                           krb5_princ_size(context, temp_client)){
                            best_client = temp_client;
                        }
                    }else{
                        best_client = temp_client;
                    }
                }
            }

        }
        i++;
    }

    if (best_client) *client = best_client;
    return 0;
}

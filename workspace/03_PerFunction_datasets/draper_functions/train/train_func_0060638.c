berEncodeAuthData(
        struct berval **requestBV,
        char    *objectDN,
        char    *pwd,
        char    *sequence,
        char    *NasIP,
        char    *state,
        int     *auth_state)
{
        int err = 0, rc=0;
        BerElement *requestBer = NULL;

        char    * utf8ObjPtr = NULL;
        int     utf8ObjSize = 0;
        char    * utf8PwdPtr = NULL;
        int     utf8PwdSize = 0;
        char    * utf8NasIPPtr = NULL;
        int     utf8NasIPSize = 0;
        char    * utf8StatePtr = NULL;
        int     utf8StateSize = 0;
        char    * utf8SeqPtr = NULL;
        int     utf8SeqSize = 0;
        int state_present = 0;

        utf8ObjSize = strlen(objectDN)+1;
        utf8ObjPtr = objectDN;

        utf8PwdSize = strlen(pwd);
        utf8PwdPtr = pwd;

        utf8SeqSize = strlen(sequence)+1;
        utf8SeqPtr = sequence;

        utf8NasIPSize = strlen(NasIP)+1;
        utf8NasIPPtr = NasIP;


        if((requestBer = ber_alloc()) == NULL)
        {
                err = NMAS_E_FRAG_FAILURE;
                goto Cleanup;
        }


        rc = ber_printf(requestBer, "{i", RADAUTH_LDAP_EXT_VERSION);
        rc = ber_printf(requestBer, "o", utf8ObjPtr, utf8ObjSize);
        rc = ber_printf(requestBer, "o", utf8PwdPtr, utf8PwdSize);
        rc = ber_printf(requestBer, "o", utf8SeqPtr, utf8SeqSize);
        rc = ber_printf(requestBer, "o", utf8NasIPPtr, utf8NasIPSize);

        if( *auth_state == -2)
        {
                utf8StateSize = strlen(state)+1;
                utf8StatePtr = state;
                state_present = 1;
                rc = ber_printf(requestBer, "io}", state_present, utf8StatePtr, utf8StateSize);
        }
        else
        {
                rc = ber_printf(requestBer, "i}", state_present);
        }

        if (rc < 0)
        {
                err = NMAS_E_FRAG_FAILURE;
                goto Cleanup;
        }
        else
        {
                err = 0;
        }


        if(ber_flatten(requestBer, requestBV) == -1)
        {
                err = NMAS_E_FRAG_FAILURE;
                goto Cleanup;
        }

Cleanup:

        if(requestBer)
        {
                ber_free(requestBer, 1);
        }

        return err;
}

pkix_pl_HttpDefaultClient_KeepAliveSessionFcn(
        SEC_HTTP_SERVER_SESSION session,
        PRPollDesc **pPollDesc)
{
        PKIX_Error *err = pkix_pl_HttpDefaultClient_KeepAliveSession
                (session, pPollDesc, plContext);

        if (err) {
                PKIX_PL_Object_DecRef((PKIX_PL_Object *)err, plContext);
                return SECFailure;
        }
        return SECSuccess;
}

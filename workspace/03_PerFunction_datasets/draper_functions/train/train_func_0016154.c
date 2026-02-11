modperl_hook_create_request(request_rec *r)
{
    MP_dRCFG;

    modperl_config_req_init(r, rcfg);


    MpReqPARSE_HEADERS_On(rcfg);

    return OK;
}

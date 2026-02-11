modperl_global_request_cfg_set(request_rec *r)
{
    MP_dDCFG;
    MP_dRCFG;


    if (MpDirGLOBAL_REQUEST(dcfg) && !MpReqSET_GLOBAL_REQUEST(rcfg)) {
        modperl_global_request_set(r);
    }
}

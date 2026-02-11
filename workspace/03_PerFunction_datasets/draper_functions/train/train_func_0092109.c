ccp_up(fsm *f)
{
    int unit;
    ccp_options *go;
    ccp_options *ho;
    char method1[64];

    if(f->protocol == PPP_CCP)
       unit = lns[f->unit].ccp_unit;
    else
       unit = lns[f->unit].ccp_l_unit;

    go = &ccp_gotoptions[unit];
    ho = &ccp_hisoptions[unit];

    ccp_flags_set(unit, 1, 1);
    if (ANY_COMPRESS(*go)) {
       if (ANY_COMPRESS(*ho)) {
           if (go->method == ho->method) {
               syslog(LOG_NOTICE, "[%d] %s compression enabled",f->unit,
                      method_name(go, ho));
           } else {
               strcpy(method1, method_name(go, NULL));
               syslog(LOG_NOTICE, "[%d] %s / %s compression enabled",f->unit,
                      method1, method_name(ho, NULL));
           }
       } else
           syslog(LOG_NOTICE, "[%d] %s receive compression enabled",f->unit,
                  method_name(go, NULL));
    } else if (ANY_COMPRESS(*ho))
       syslog(LOG_NOTICE, "[%d] %s transmit compression enabled",f->unit,
	 method_name(ho, NULL));
}

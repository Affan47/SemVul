do_ps_service(Slapi_Entry *e, Slapi_Entry *eprev, ber_int_t chgtype, ber_int_t chgnum)
{
    if (NULL == ps_service_fn) {
        if (get_entry_point(ENTRY_POINT_PS_SERVICE, (caddr_t *)(&ps_service_fn)) < 0) {
            return;
        }
    }
    (ps_service_fn)(e, eprev, chgtype, chgnum);
}

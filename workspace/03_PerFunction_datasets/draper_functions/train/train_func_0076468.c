output_body(request_rec *r, SV *body)
{
    dTHX;
    int rc, type;
    switch (type = SvTYPE(SvRV(body))) {
        case SVt_PVAV:
            rc = output_body_ary(r, (AV *) SvRV(body));
            break;
        case SVt_PVGV:


            require_pv("IO/Handle.pm");
        case SVt_PVMG:
            if (respond_to(body, "path")) {
                rc = output_body_path(r, body);
                if (rc != DECLINED) break;
            }
            rc = output_body_obj(r, body, type);
            break;
        default:
            server_error(r, "response body must be an array reference or object");
            rc = HTTP_INTERNAL_SERVER_ERROR;
            break;
    }
    return rc;
}

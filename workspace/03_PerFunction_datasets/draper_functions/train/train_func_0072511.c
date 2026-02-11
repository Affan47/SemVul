setup_choice_response(request_rec *r, negotiation_state *neg,
                                 var_rec *variant)
{
    request_rec *sub_req;
    const char *sub_vary;

    if (!variant->sub_req) {
        int status;

        sub_req = ap_sub_req_lookup_file(variant->file_name, r, r->output_filters);
        status = sub_req->status;

        if (status != HTTP_OK &&
            !apr_table_get(sub_req->err_headers_out, "TCN")) {
            ap_destroy_sub_req(sub_req);
            return status;
        }
        variant->sub_req = sub_req;
    }
    else {
        sub_req = variant->sub_req;
    }


    if (neg->is_transparent &&
        apr_table_get(sub_req->err_headers_out, "TCN")) {
        return HTTP_VARIANT_ALSO_VARIES;
    }


    if (sub_req->handler && strcmp(sub_req->handler, "type-map") == 0) {
        return HTTP_VARIANT_ALSO_VARIES;
    }


    if ((sub_vary = apr_table_get(sub_req->err_headers_out, "Vary")) != NULL) {
        apr_table_setn(r->err_headers_out, "Variant-Vary", sub_vary);


        apr_table_setn(r->err_headers_out, "Vary", sub_vary);
        apr_table_unset(sub_req->err_headers_out, "Vary");
    }

    apr_table_setn(r->err_headers_out, "Content-Location",
                  ap_escape_path_segment(r->pool, variant->file_name));

    set_neg_headers(r, neg, alg_choice);


    return 0;
}

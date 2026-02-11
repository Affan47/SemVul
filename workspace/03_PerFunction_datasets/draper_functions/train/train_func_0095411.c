split_on_bdry(apr_bucket_brigade *out,
                                  apr_bucket_brigade *in,
                                  const apr_strmatch_pattern *pattern,
                                  const char *bdry)
{
    apr_bucket *e = APR_BRIGADE_FIRST(in);
    apr_size_t blen = strlen(bdry), off = 0;

    while ( e != APR_BRIGADE_SENTINEL(in) ) {
        apr_ssize_t idx;
        apr_size_t len;
        const char *buf;
        apr_status_t s;

        if (APR_BUCKET_IS_EOS(e))
            return APR_EOF;

        s = apr_bucket_read(e, &buf, &len, APR_BLOCK_READ);
        if (s != APR_SUCCESS)
            return s;

        if (len == 0) {
            apr_bucket *f = e;
            e = APR_BUCKET_NEXT(e);
            apr_bucket_delete(f);
            continue;
        }

    look_for_boundary_up_front:
        if (strncmp(bdry + off, buf, MIN(len, blen - off)) == 0) {
            if ( len >= blen - off ) {

                if (len > blen - off)
                    apr_bucket_split(e, blen - off);
                e = APR_BUCKET_NEXT(e);

                do {
                    apr_bucket *f = APR_BRIGADE_FIRST(in);
                    apr_bucket_delete(f);
                } while (APR_BRIGADE_FIRST(in) != e);

                return APR_SUCCESS;
            }

            off += len;
            e = APR_BUCKET_NEXT(e);
            continue;
        }
        else if (off > 0) {


            apr_bucket_brigade * volatile in_v = in;

            do {
                apr_bucket *f = APR_BRIGADE_FIRST(in_v);
                APR_BUCKET_REMOVE(f);
                APR_BRIGADE_INSERT_TAIL(out, f);
            } while (e != APR_BRIGADE_FIRST(in_v));
            off = 0;
            goto look_for_boundary_up_front;
        }

        if (pattern != NULL && len >= blen) {
            const char *match = apr_strmatch(pattern, buf, len);
            if (match != NULL)
                idx = match - buf;
            else {
                idx = apreq_index(buf + len-blen, blen, bdry, blen,
                                  APREQ_MATCH_PARTIAL);
                if (idx >= 0)
                    idx += len-blen;
            }
        }
        else
            idx = apreq_index(buf, len, bdry, blen, APREQ_MATCH_PARTIAL);


        if (idx >= 0)
            apr_bucket_split(e, idx);

        APR_BUCKET_REMOVE(e);
        APR_BRIGADE_INSERT_TAIL(out, e);
        e = APR_BRIGADE_FIRST(in);
    }

    return APR_INCOMPLETE;
}

cached_explode(apr_time_exp_t *xt, apr_time_t t,
                                   struct exploded_time_cache_element *cache,
                                   int use_gmt)
{
    apr_int64_t seconds = apr_time_sec(t);
    struct exploded_time_cache_element *cache_element =
        &(cache[seconds & TIME_CACHE_MASK]);
    struct exploded_time_cache_element cache_element_snapshot;


    if (cache_element->t >= seconds) {


        memcpy(&cache_element_snapshot, cache_element,
               sizeof(struct exploded_time_cache_element));
        if ((seconds != cache_element_snapshot.t) ||
            (seconds != cache_element_snapshot.t_validate)) {

            if (use_gmt) {
                return apr_time_exp_gmt(xt, t);
            }
            else {
                return apr_time_exp_lt(xt, t);
            }
        }
        else {

            memcpy(xt, &(cache_element_snapshot.xt),
                   sizeof(apr_time_exp_t));
        }
    }
    else {
        apr_status_t r;
        if (use_gmt) {
            r = apr_time_exp_gmt(xt, t);
        }
        else {
            r = apr_time_exp_lt(xt, t);
        }
        if (r != APR_SUCCESS) {
            return r;
        }
        cache_element->t = seconds;
        memcpy(&(cache_element->xt), xt, sizeof(apr_time_exp_t));
        cache_element->t_validate = seconds;
    }
    xt->tm_usec = (int)apr_time_usec(t);
    return APR_SUCCESS;
}

data_copy (data_t *old)
{
        if (!old) {
                gf_log_callingfn ("dict", GF_LOG_WARNING,
                                  "old is NULL");
                return NULL;
        }

        data_t *newdata = (data_t *) GF_CALLOC (1, sizeof (*newdata),
                                                gf_common_mt_data_t);

        if (!newdata) {
                return NULL;
        }

        if (old) {
                newdata->len = old->len;
                if (old->data) {
                        newdata->data = memdup (old->data, old->len);
                        if (!newdata->data)
                                goto err_out;
                }
                if (old->vec) {
                        newdata->vec = memdup (old->vec, old->len * (sizeof (void *) +
                                                                     sizeof (size_t)));
                        if (!newdata->vec)
                                goto err_out;
                }
        }

        LOCK_INIT (&newdata->lock);
        return newdata;

err_out:

        if (newdata->data)
                FREE (newdata->data);
        if (newdata->vec)
                FREE (newdata->vec);
        GF_FREE (newdata);

        return NULL;
}

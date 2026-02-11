transaction_lk_op (afr_local_t *local)
{
        afr_internal_lock_t *int_lock = NULL;
        int ret = -1;

        int_lock = &local->internal_lock;

        if (int_lock->transaction_lk_type == AFR_TRANSACTION_LK) {
                gf_log (THIS->name, GF_LOG_DEBUG,
                        "lk op is for a transaction");
                ret = 1;
        }
        else if (int_lock->transaction_lk_type == AFR_SELFHEAL_LK) {
                gf_log (THIS->name, GF_LOG_DEBUG,
                        "lk op is for a self heal");

                ret = 0;
        }

        if (ret == -1)
                gf_log (THIS->name, GF_LOG_DEBUG,
                        "lk op is not set");

        return ret;

}

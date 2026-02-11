set_solution(struct ntb_pow_cookie *cookie,
             uint64_t nonce)
{
        struct ntb_pow *pow = cookie->pow;

        pthread_mutex_lock(&pow->mutex);


        if (!cookie->done) {
                cookie->nonce = nonce;
                cookie->done = true;
                cookie->idle_source =
                        ntb_main_context_add_idle(NULL, idle_cb, cookie);

                cookie->ref_count++;
        }

        pthread_mutex_unlock(&pow->mutex);
}

slapi_compute_add_evaluator(slapi_compute_callback_t function)
{
	int rc = 0;
	compute_evaluator *new_eval = NULL;
	PR_ASSERT(NULL != function);
	PR_ASSERT(NULL != compute_evaluators_lock);
        if (startup_completed) {


            require_compute_evaluator_lock = PR_TRUE;
        }

	new_eval = (compute_evaluator *)slapi_ch_calloc(1,sizeof (compute_evaluator));
	if (NULL == new_eval) {
		rc = ENOMEM;
	} else {
                int need_lock = require_compute_evaluator_lock;

                if (need_lock) {
                    slapi_rwlock_wrlock(compute_evaluators_lock);
                }

                compute_add_evaluator_nolock(function, new_eval);

                if (need_lock) {
                    slapi_rwlock_unlock(compute_evaluators_lock);
                }
	}

	return rc;
}

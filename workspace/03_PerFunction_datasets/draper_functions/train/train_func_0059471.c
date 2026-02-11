eq_enqueue(slapi_eq_context *newec)
{
	slapi_eq_context **p;

	PR_ASSERT(NULL != newec);
	PR_Lock(eq->eq_lock);

	for (p = &(eq->eq_queue); *p != NULL; p = &((*p)->ec_next)) {
		if ((*p)->ec_when > newec->ec_when) {
			break;
		}
	}
	if (NULL != *p) {
		newec->ec_next = *p;
	} else {
		newec->ec_next = NULL;
	}
	*p = newec;
	PR_NotifyCondVar(eq->eq_cv);
	PR_Unlock(eq->eq_lock);
}

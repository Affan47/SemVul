cr_spinlock_lock(cr_spinlock_t *x)
{
    cri_atomic_t *p = (cri_atomic_t *)x;

    if (!cri_cmp_swap(p, CRI_SL_UNLOCKED, CRI_SL_LOCKED)) {
#if CRI_SL_DEBUG
	cri_atomic_t tmp = cri_atomic_read(p);

	if ((tmp != CRI_SL_LOCKED) && (tmp != CRI_SL_UNLOCKED)) {
	    CRI_ABORT("Spinlock %p has invalid state %x", p, tmp);
	}
#endif

	CRI_DO_YIELD_WHILE_COND(!cri_cmp_swap(p, CRI_SL_UNLOCKED, CRI_SL_LOCKED));
    }
}

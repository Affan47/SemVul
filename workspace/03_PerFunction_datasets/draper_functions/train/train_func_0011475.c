__env_alloc_free(infop, ptr)
	REGINFO *infop;
	void *ptr;
{
	ALLOC_ELEMENT *elp, *elp_tmp;
	ALLOC_LAYOUT *head;
	ENV *env;
	SIZEQ_HEAD *q;
	size_t len;
	u_int8_t i, *p;

	env = infop->env;


	if (F_ISSET(env, ENV_PRIVATE)) {

		p = (u_int8_t *)((uintmax_t *)ptr - 1);
		len = (size_t)*(uintmax_t *)p;

		infop->allocated -= len;
		if (F_ISSET(infop, REGION_SHARED))
			env->reginfo->allocated -= len;

#ifdef DIAGNOSTIC

		DB_ASSERT(env, p[len - 1] == GUARD_BYTE);


		memset(p, CLEAR_BYTE, len);
#endif
		__os_free(env, p);
		return;
	}

#ifdef HAVE_MUTEX_SUPPORT
	MUTEX_REQUIRED(env, infop->mtx_alloc);
#endif

	head = infop->head;

	p = ptr;
	elp = (ALLOC_ELEMENT *)(p - sizeof(ALLOC_ELEMENT));

	STAT_INC_VERB(env, mpool, free, head->freed, elp->ulen, infop->id);

#ifdef DIAGNOSTIC

	DB_ASSERT(env, p[elp->ulen] == GUARD_BYTE);


	memset(p, CLEAR_BYTE, (size_t)elp->len - sizeof(ALLOC_ELEMENT));
#endif


	elp->ulen = 0;


	if ((elp_tmp =
	    SH_TAILQ_PREV(&head->addrq, elp, addrq, __alloc_element)) != NULL &&
	    elp_tmp->ulen == 0 &&
	    (u_int8_t *)elp_tmp + elp_tmp->len == (u_int8_t *)elp) {


		SH_TAILQ_REMOVE(&head->addrq, elp, addrq, __alloc_element);
		SET_QUEUE_FOR_SIZE(head, q, i, elp_tmp->len);
		SH_TAILQ_REMOVE(q, elp_tmp, sizeq, __alloc_element);

		elp_tmp->len += elp->len;
		elp = elp_tmp;
	}
	if ((elp_tmp = SH_TAILQ_NEXT(elp, addrq, __alloc_element)) != NULL &&
	    elp_tmp->ulen == 0 &&
	    (u_int8_t *)elp + elp->len == (u_int8_t *)elp_tmp) {


		SH_TAILQ_REMOVE(&head->addrq, elp_tmp, addrq, __alloc_element);
		SET_QUEUE_FOR_SIZE(head, q, i, elp_tmp->len);
		SH_TAILQ_REMOVE(q, elp_tmp, sizeq, __alloc_element);

		elp->len += elp_tmp->len;
	}


	__env_size_insert(head, elp);
}

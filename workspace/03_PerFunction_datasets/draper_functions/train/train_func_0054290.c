g2_qht_put(struct qhtable *to_free)
{
	if(!to_free)
		return;

	if(atomic_dec_test(&to_free->refcnt))
		hzp_deferfree(&to_free->hzp, to_free, g2_qht_free_hzp);
	else if(atomic_read(&to_free->refcnt) < 0)
		logg_develd("qht refcnt below zero! %p %i\n", (void*)to_free, atomic_read(&to_free->refcnt));
}

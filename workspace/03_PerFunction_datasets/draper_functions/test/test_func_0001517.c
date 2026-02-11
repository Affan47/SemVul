smt_free_mbuf(struct s_smc *smc, SMbuf *mb)
{

	if (mb) {
		mb->sm_use_count-- ;
		DB_GEN("free_mbuf: sm_use_count = %d",mb->sm_use_count,0,3) ;


		if (!mb->sm_use_count) {
			DB_GEN("free SMbuf: mb = %x",(void *)mb,0,3) ;
#ifndef	COMMON_MB_POOL
			mb->sm_next = smc->os.hwm.mbuf_pool.mb_free ;
			smc->os.hwm.mbuf_pool.mb_free = mb ;
#else
			mb->sm_next = mb_free ;
			mb_free = mb ;
#endif
		}
	}
	else
		SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ;
}

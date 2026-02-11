csio_wr_cleanup_iq_ftr(struct csio_hw *hw, int qidx)
{
	struct csio_wrm *wrm	= csio_hw_to_wrm(hw);
	struct csio_q	*q	= wrm->q_arr[qidx];
	void *wr;
	struct csio_iqwr_footer *ftr;
	uint32_t i = 0;


	q->un.iq.genbit = 1;

	for (i = 0; i < q->credits; i++) {

		wr = (void *)((uintptr_t)q->vstart +
					   (i * q->wr_sz));

		ftr = (struct csio_iqwr_footer *)((uintptr_t)wr +
					  (q->wr_sz - sizeof(*ftr)));

		memset(ftr, 0, sizeof(*ftr));
	}
}

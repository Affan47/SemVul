hwi_ring_cq_db(struct beiscsi_hba *phba,
			   unsigned int id, unsigned int num_processed,
			   unsigned char rearm, unsigned char event)
{
	u32 val = 0;

	if (rearm)
		val |= 1 << DB_CQ_REARM_SHIFT;

	val |= num_processed << DB_CQ_NUM_POPPED_SHIFT;


	val |= (id & DB_CQ_RING_ID_LOW_MASK);


	val |= (((id >> DB_CQ_HIGH_FEILD_SHIFT) &
		  DB_CQ_RING_ID_HIGH_MASK)
		  << DB_CQ_HIGH_SET_SHIFT);

	iowrite32(val, phba->db_va + DB_CQ_OFFSET);
}

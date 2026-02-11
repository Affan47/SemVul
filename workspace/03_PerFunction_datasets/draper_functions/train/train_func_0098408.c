falcon_notify_tx_desc ( struct efab_nic *efab,
			struct efab_tx_queue *tx_queue )
{
	efab_dword_t reg;
	int ptr = tx_queue->write_ptr % EFAB_TXD_SIZE;

	EFAB_POPULATE_DWORD_1 ( reg, FCN_TX_DESC_WPTR_DWORD, ptr );
	falcon_writel ( efab, &reg, FCN_TX_DESC_UPD_REG_KER_DWORD );
}

check_for_missing_tx_completions(struct ena_adapter *adapter)
{
	struct ena_ring *tx_ring;
	int i, budget, rc;


	smp_rmb();

	if (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		return;

	if (test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))
		return;

	if (adapter->missing_tx_completion_to == ENA_HW_HINTS_NO_TIMEOUT)
		return;

	budget = ENA_MONITORED_TX_QUEUES;

	for (i = adapter->last_monitored_tx_qid; i < adapter->num_queues; i++) {
		tx_ring = &adapter->tx_ring[i];

		rc = check_missing_comp_in_queue(adapter, tx_ring);
		if (unlikely(rc))
			return;

		budget--;
		if (!budget)
			break;
	}

	adapter->last_monitored_tx_qid = i % adapter->num_queues;
}

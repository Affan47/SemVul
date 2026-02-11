qede_sp_task(struct work_struct *work)
{
	struct qede_dev *edev = container_of(work, struct qede_dev,
					     sp_task.work);
	mutex_lock(&edev->qede_lock);

	if (edev->state == QEDE_STATE_OPEN) {
		if (test_and_clear_bit(QEDE_SP_RX_MODE, &edev->sp_flags))
			qede_config_rx_mode(edev->ndev);
	}

	mutex_unlock(&edev->qede_lock);
}

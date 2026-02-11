mlxsw_pci_eq_irq_handler(int irq, void *dev_id)
{
	struct mlxsw_pci *mlxsw_pci = dev_id;
	struct mlxsw_pci_queue *q;
	int i;

	for (i = 0; i < MLXSW_PCI_EQS_COUNT; i++) {
		q = mlxsw_pci_eq_get(mlxsw_pci, i);
		mlxsw_pci_queue_tasklet_schedule(q);
	}
	return IRQ_HANDLED;
}

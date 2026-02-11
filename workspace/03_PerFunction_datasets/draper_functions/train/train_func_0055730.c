RemovePartition(void)
{
	workingPackageData.GetFirmwareInfo().GetFileInfos().removeAt(partitionsListWidget->currentRow());
	UpdateUnusedPartitionIds();

	QListWidgetItem *item = partitionsListWidget->currentItem();
	partitionsListWidget->setCurrentRow(-1);
	delete item;

	pitBrowseButton->setEnabled(true);
	addPartitionButton->setEnabled(true);
	partitionsListWidget->setEnabled(true);
	UpdateInterfaceAvailability();
}

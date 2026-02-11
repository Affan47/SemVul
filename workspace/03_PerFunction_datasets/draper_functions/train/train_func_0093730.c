SelectPartitionName(int index)
{
	if (!populatingPartitionNames && index != -1 && index != unusedPartitionIds.length())
	{
		unsigned int newPartitionIndex = unusedPartitionIds[index];
		unusedPartitionIds.removeAt(index);

		FileInfo& fileInfo = workingPackageData.GetFirmwareInfo().GetFileInfos()[partitionsListWidget->currentRow()];
		unusedPartitionIds.append(fileInfo.GetPartitionId());
		fileInfo.SetPartitionId(newPartitionIndex);

		PitEntry *pitEntry = currentPitData.FindEntry(newPartitionIndex);

		QString title("File");

		if (pitEntry && strlen(pitEntry->GetFlashFilename()) > 0)
			title += " (" + QString(pitEntry->GetFlashFilename()) + ")";

		partitionFileGroup->setTitle(title);

		if (!fileInfo.GetFilename().isEmpty())
		{
			QString partitionFilename = pitEntry->GetFlashFilename();
			int lastPeriod = partitionFilename.lastIndexOf(QChar('.'));

			if (lastPeriod >= 0)
			{
				QString partitionFileExtension = partitionFilename.mid(lastPeriod + 1);

				lastPeriod = fileInfo.GetFilename().lastIndexOf(QChar('.'));

				if (lastPeriod < 0 || fileInfo.GetFilename().mid(lastPeriod + 1) != partitionFileExtension)
					Alerts::DisplayWarning(QString("%1 partition expects files with file extension \"%2\".").arg(pitEntry->GetPartitionName(), partitionFileExtension));
			}
		}

		partitionNameComboBox->clear();


		UpdatePartitionNamesInterface();
		partitionIdLineEdit->setText(QString::number(newPartitionIndex));
		partitionsListWidget->currentItem()->setText(currentPitData.FindEntry(newPartitionIndex)->GetPartitionName());
	}
}

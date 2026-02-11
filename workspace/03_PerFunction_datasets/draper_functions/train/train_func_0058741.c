setupPartitionFlashInfo(const vector<PartitionFile>& partitionFiles, const PitData *pitData, vector<PartitionFlashInfo>& partitionFlashInfos)
{
	for (vector<PartitionFile>::const_iterator it = partitionFiles.begin(); it != partitionFiles.end(); it++)
	{
		const PitEntry *pitEntry = nullptr;


		unsigned int partitionIdentifier;

		if (Utility::ParseUnsignedInt(partitionIdentifier, it->argumentName) == kNumberParsingStatusSuccess)
		{
			pitEntry = pitData->FindEntry(partitionIdentifier);

			if (!pitEntry)
			{
				Interface::PrintError("No partition with identifier \"%s\" exists in the specified PIT.\n", it->argumentName);
				return (false);
			}
		}
		else
		{

			pitEntry = pitData->FindEntry(it->argumentName);

			if (!pitEntry)
			{
				Interface::PrintError("Partition \"%s\" does not exist in the specified PIT.\n", it->argumentName);
				return (false);
			}
		}

		partitionFlashInfos.push_back(PartitionFlashInfo(pitEntry, it->file));
	}

	return (true);
}

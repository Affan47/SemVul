isStorageVolume() const
{
    return isPartition() || isPartitionTable() || isStorageAccess() || isOpticalDisc();
}

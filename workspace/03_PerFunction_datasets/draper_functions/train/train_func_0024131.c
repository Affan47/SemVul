bad_cluster(DOS_FS * fs, unsigned long cluster)
{
    FAT_ENTRY curEntry;
    get_fat(&curEntry, fs->fat, cluster, fs);

    return FAT_IS_BAD(fs, curEntry.value);
}

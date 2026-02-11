archive_entry_devminor(struct archive_entry *entry)
{
    if (entry->ae_stat.aest_dev_is_broken_down)
        return (entry->ae_stat.aest_devminor);
    else
        return minor(entry->ae_stat.aest_dev);
}

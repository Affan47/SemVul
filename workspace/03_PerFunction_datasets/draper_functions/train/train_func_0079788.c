index_lock_group(int fd, ptrdiff_t offset, enum inn_locktype type)
{
    bool status;
    size_t size;

    size = sizeof(struct group_entry);
    offset = offset * size + sizeof(struct group_header);
    status = inn_lock_range(fd, type, true, offset, size);
    if (!status)
        syswarn("tradindexed: cannot %s group entry at %lu",
                (type == INN_LOCK_UNLOCK) ? "unlock" : "lock",
                (unsigned long) offset);
    return status;
}

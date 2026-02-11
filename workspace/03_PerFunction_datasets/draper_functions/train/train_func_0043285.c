get_lock_value(const void *lock, int lock_size)
{
    uint64_t lock_value = 0;

    if (lock_size == 4) {
        lock_value = *(uint32_t *) lock;
    } else if (lock_size == 8) {
        lock_value = *(uint64_t *) lock;
    }

    return lock_value;
}

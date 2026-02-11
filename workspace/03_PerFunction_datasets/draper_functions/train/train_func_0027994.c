__get_lock_length (off_t start, off_t end)
{
        if (end == LLONG_MAX)
                return 0;
        else
                return (end - start + 1);
}

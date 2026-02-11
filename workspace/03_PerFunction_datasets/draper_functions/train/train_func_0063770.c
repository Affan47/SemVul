make_new_offset(int p_size, int step)
{
    int new_offset;
    if (step > 0) {
        new_offset = PREFETCH_CACHE_SIZE / p_size * step;
    } else {
        new_offset = PREFETCH_CACHE_SIZE / p_size * step + step + 1;
    }
    return new_offset;
}

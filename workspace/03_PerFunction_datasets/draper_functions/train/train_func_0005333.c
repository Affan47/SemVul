il_compute_scroll()
{
    return max((il->columns - il->static_length) / 4,  1);
}

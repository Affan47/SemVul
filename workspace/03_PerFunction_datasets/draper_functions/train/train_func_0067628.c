get_sequence_position(const ED4_base *base, int base_pos)
{
    if (!base) return 0;
    if (base!=calced4base) calc4base(base);
    return base_pos<count ? seq_pos[base_pos] : seq_pos[count-1]+1;
}

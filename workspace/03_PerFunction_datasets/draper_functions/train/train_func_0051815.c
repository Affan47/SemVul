read_fixed_64(struct bc_read_stream *stream, int num_bits)
{
    if(num_bits <= 32)
    {
        return read_fixed(stream, num_bits);
    }
    else
    {
        uint64_t ret = read_fixed(stream, 32);
        return ret | ((uint64_t)read_fixed(stream, num_bits-32) << 32);
    }
}

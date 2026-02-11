waitforsent(_u32 timeout, size_t * returned_size)
{
    if (returned_size) *returned_size = required_tx_cnt;
    return 0;
}

final()
{

    uint64 total_bits = (transforms*BLOCK_BYTES + buffer.size()) * 8;


    buffer += 0x80;
    unsigned int orig_size = buffer.size();
    while (buffer.size() < BLOCK_BYTES)
    {
        buffer += (char)0x00;
    }

    uint32 block[BLOCK_INTS];
    buffer_to_block(buffer, block);

    if (orig_size > BLOCK_BYTES - 8)
    {
        transform(block);
        for (unsigned int i = 0; i < BLOCK_INTS - 2; i++)
        {
            block[i] = 0;
        }
    }


    block[BLOCK_INTS - 1] = total_bits;
    block[BLOCK_INTS - 2] = (total_bits >> 32);
    transform(block);


    std::ostringstream result;
    for (unsigned int i = 0; i < DIGEST_INTS; i++)
    {
        result << std::hex << std::setfill('0') << std::setw(8);
        result << (digest[i] & 0xffffffff);
    }


    reset();

    return result.str();
}

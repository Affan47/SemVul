H5T_bit_inc(uint8_t *buf, size_t start, size_t size)
{
    size_t	idx = start / 8;
    unsigned	carry = 1;
    unsigned	acc, mask;


    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5T_bit_inc)

    HDassert(buf);

    start %= 8;


    if(start) {
	if(size + start < 8)
            mask = ((unsigned)1 << size) - 1;
	else
            mask = ((unsigned)1 << (8 - start)) - 1;
	acc = ((unsigned)buf[idx] >> start) & mask;
	acc++;
	carry = acc & ((unsigned)1 << MIN(size, 8 - start));
	buf[idx] &= (uint8_t)(~(mask << start));
	buf[idx] |= (uint8_t)((acc & mask) << start);
	size -= MIN(size, 8 - start);
	start = 0;
	idx++;
    }


    while(carry && size >= 8) {
	acc = buf[idx];
	acc++;
	carry = acc & 0x100;
	buf[idx] = acc & 0xff;
	idx++;
	size -= 8;
    }


    if(carry && size > 0) {
	mask = ((unsigned)1 << size) - 1;
	acc = buf[idx] & mask;
	acc++;
	carry = acc & ((unsigned)1 << size);
	buf[idx] &= (uint8_t)(~mask);
	buf[idx] |= (uint8_t)(acc & mask);
    }

    FUNC_LEAVE_NOAPI(carry ? TRUE : FALSE)
}

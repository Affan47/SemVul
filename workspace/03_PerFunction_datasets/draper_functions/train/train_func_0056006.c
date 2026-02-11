H5T__bit_neg(uint8_t *buf, size_t start, size_t size)
{
    size_t	idx = start / 8;
    size_t      pos = start % 8;
    uint8_t     tmp[1];


    FUNC_ENTER_PACKAGE_NOERR

    HDassert(buf);
    HDassert(size);


    tmp[0] = (uint8_t)~buf[idx];


    if((size + start - 1) / 8 > idx) {
        H5T__bit_copy(&(buf[idx]), pos, tmp, pos, (8-pos));
        idx++;
        size -= (8 - pos);


        while(size >= 8) {
            buf[idx] = (uint8_t)~(buf[idx]);
            idx++;
            size -= 8;
        }


        if(size > 0) {

            tmp[0] = (uint8_t)~buf[idx];
            H5T__bit_copy(&(buf[idx]), (size_t)0, tmp, (size_t)0, size);
        }
    }
    else
        H5T__bit_copy(&(buf[idx]), pos, tmp, pos, size);

    FUNC_LEAVE_NOAPI_VOID
}

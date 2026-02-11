get_is_dc_yuv(struct rbitstream*str)
{
    if (_jxr_rbitstream_uint1(str) == 1) {
        if (_jxr_rbitstream_uint1(str) == 1)
            return 4;
        else
            return 0;
    }
    else {
        switch (_jxr_rbitstream_uint2(str)) {
            case 0:
                if (_jxr_rbitstream_uint1(str) == 1)
                    return 3;
                else if (_jxr_rbitstream_uint1(str) == 1)
                    return 2;
                else
                    return 6;
            case 1:
                return 1;

            case 2:
                return 5;

            case 3:
                return 7;
        }
    }

    assert(0);
    return -1;
}

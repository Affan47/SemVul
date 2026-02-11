switch_r_b(void *data, int bpi)
{
    uint32_t tmp;
    data = (uint8_t*)data;
    if(bpi == 8)
    {
        uint8_t *p = (uint8_t*)data;
        tmp = p[0];
        p[0] = p[2];
        p[2] = tmp;

    }

    else if(bpi == 16)
    {
        uint16_t *p = (uint16_t*)data;
        tmp = p[0];
        p[0] = p[2];
        p[2] = tmp;
    }
    else if(bpi == 32)
    {
        uint32_t *p = (uint32_t *)data;
        tmp = p[0];
        p[0] = p[2];
        p[2] = tmp;
    }
    else
    {
        assert(!"Invalid bpi\n");
    }
}

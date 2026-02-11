gx_dc_pure_equal(const gx_device_color * pdevc1, const gx_device_color * pdevc2)
{
    return pdevc2->type == pdevc1->type &&
        gx_dc_pure_color(pdevc1) == gx_dc_pure_color(pdevc2);
}

gx_restrict_DeviceN(gs_client_color * pcc, const gs_color_space * pcs)
{
    uint i;

    for (i = 0; i < pcs->params.device_n.num_components; ++i) {
        floatp value = pcc->paint.values[i];
        pcc->paint.values[i] = (value <= 0 ? 0 : value >= 1 ? 1 : value);
    }
}

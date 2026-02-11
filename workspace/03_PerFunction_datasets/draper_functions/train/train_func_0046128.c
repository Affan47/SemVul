_instance_validate(unsigned int inst_id, unsigned int dmasize)
{
    int i;
    bde_inst_resource_t *res;

    for (i = 0; i < user_bde->num_devices(BDE_ALL_DEVICES); i++) {
        res = &_bde_inst_resource[i];
        if (res->inst_id == inst_id) {
            if (res->dma_size != dmasize) {
                if(_devices[i].inst == 0){

                    return LUBDE_SUCCESS;
                }
                gprintk("ERROR: dma_size mismatch\n");
                return LUBDE_FAIL;
            }
            return (1);
        }
    }
    return LUBDE_SUCCESS;
}

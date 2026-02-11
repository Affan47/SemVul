daq_modify_flow(const DAQ_Module_t *module, void *handle, const DAQ_PktHdr_t *hdr, DAQ_ModFlow_t *modify)
{
    if (!module)
        return DAQ_ERROR_NOMOD;

    if (!module->modify_flow)
        return DAQ_SUCCESS;

    return module->modify_flow(handle, hdr, modify);
}

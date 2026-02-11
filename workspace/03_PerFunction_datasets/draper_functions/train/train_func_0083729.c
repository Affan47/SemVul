getValue(void *data, Query *)
{
    data = shiftPointer(data);
    if (!data) return 0;

    service *svc = (service *)data;
    switch (_type) {
        case SSIC_PNP_GRAPH_PRESENT:
            return pnpgraph_present(svc->host_ptr->name, svc->description);
    }
    return -1;
}

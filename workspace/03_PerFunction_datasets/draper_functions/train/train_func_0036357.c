epr_detect_asar_sw_version(EPR_SProductId* product_id)
{
    EPR_SDSD** elems;
    int size = 0;
    int rec_size = 0;
    int i, version = 0;
    char* name;

    if ((strncmp("ASA", product_id->id_string, 3) == 0) ||
        (strncmp("SAR", product_id->id_string, 3) == 0)) {

        elems = (EPR_SDSD**)product_id->dsd_array->elems;
        size = product_id->dsd_array->length;
        for (i=0; i< size;i++){
            name = elems[i]->ds_name;
            if (strncmp("MAIN PROCESSING PARAMS ADS", name, 26) == 0) {
                rec_size = elems[i]->dsr_size;
                if (rec_size == 10069) {
                    version = 602;
                }
                break;
            }
        }
    }

    return version;
}

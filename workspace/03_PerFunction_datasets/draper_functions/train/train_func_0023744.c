bm_get_attribute_location(BuzzMachine *bm,int index) {
    if(!(index<bm->machine_info->numAttributes)) return(0);
    if(!(bm->machine_iface->AttrVals)) return(0);

    return((void *)&bm->machine_iface->AttrVals[index]);
}

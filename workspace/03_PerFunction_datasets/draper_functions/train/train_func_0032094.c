bm_get_parameter_info(BuzzMachineHandle *bmh,int index,BuzzMachineParameter key,void *value) {
    int ret=TRUE;
    int *ival;
    const char **sval;

    ival=(int *)value;
    sval=(const char **)value;
    switch(key) {
        case BM_PARA_TYPE:            *ival=bmh->machine_info->Parameters[index]->Type;break;
        case BM_PARA_NAME:            *sval=bmh->machine_info->Parameters[index]->Name;break;
        case BM_PARA_DESCRIPTION:     *sval=bmh->machine_info->Parameters[index]->Description;break;
        case BM_PARA_MIN_VALUE:       *ival=bmh->machine_info->Parameters[index]->MinValue;break;
        case BM_PARA_MAX_VALUE:       *ival=bmh->machine_info->Parameters[index]->MaxValue;break;
        case BM_PARA_NO_VALUE:        *ival=bmh->machine_info->Parameters[index]->NoValue;break;
        case BM_PARA_FLAGS:           *ival=bmh->machine_info->Parameters[index]->Flags;break;
        case BM_PARA_DEF_VALUE:       *ival=bmh->machine_info->Parameters[index]->DefValue;break;
        default: ret=FALSE;
    }
    return(ret);
}

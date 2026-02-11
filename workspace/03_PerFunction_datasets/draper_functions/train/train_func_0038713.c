make_trans_group(qr_operator qr_ope,
                 List *param,
                 int syncs_mt)
{
    Trans_group *transg;
    transg = alloc_trans_group();
    transg->kind = qr_ope;
    switch(qr_ope) {
    case OPE_DTU_CHECKF:
        transg->checkf = list_concat(transg->checkf, param);
        break;
    case OPE_DTU_KICK:
        transg->kick = list_concat(transg->kick, param);
        break;
    case OPE_MT_SYNCR:
        transg->syncs_mt = syncs_mt;
        break;
    default:
        fatal("Unexpected Situation\n");
        break;
    }
    return transg;
}

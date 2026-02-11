bkn_knet_dev_inst_set(kcom_msg_version_t *kmsg)
{
    bkn_switch_info_t *sinfo;
    int d = kmsg->hdr.unit;
    uint32 inst = 0;
    unsigned long flags;
    struct list_head *list;

    sinfo = bkn_sinfo_from_unit(d);
    lkbde_dev_instid_get(d, &inst);

    spin_lock_irqsave(&sinfo->lock, flags);
    if (sinfo->inst_id != inst) {

        sinfo->inst_id = 0;
        sinfo->evt_idx = -1;
    }
    spin_unlock_irqrestore(&sinfo->lock, flags);

    if (inst) {
        if (sinfo->inst_id == 0){
            if (bkn_create_inst(inst) != 0) {
                return -1;
            }
        }
        spin_lock_irqsave(&sinfo->lock, flags);
        sinfo->inst_id = inst;
        spin_unlock_irqrestore(&sinfo->lock, flags);
    } else {

        list_for_each(list, &_sinfo_list) {
            sinfo = (bkn_switch_info_t *)list;
            spin_lock_irqsave(&sinfo->lock, flags);
            sinfo->evt_idx = 0;
            sinfo->inst_id = 0;
            spin_unlock_irqrestore(&sinfo->lock, flags);
        }
    }
    return 0;
}

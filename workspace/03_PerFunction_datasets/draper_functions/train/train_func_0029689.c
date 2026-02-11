smscenter_submit_msg(SMSCenter *smsc, Msg *msg)
{
    smscenter_lock(smsc);

    switch (smsc->type) {

    case SMSC_TYPE_CIMD:
        if (cimd_submit_msg(smsc, msg) == -1)
            goto error;
        break;

    case SMSC_TYPE_EMI_X25:
        if (emi_submit_msg(smsc, msg) == -1)
            goto error;
        break;

    case SMSC_TYPE_SEMA_X28:
        if (sema_submit_msg(smsc, msg) == -1)
            goto error;
        break;

    case SMSC_TYPE_OIS:
        if (ois_submit_msg(smsc, msg) == -1)
            goto error;
        break;


    default:
        goto error;
    }

    smscenter_unlock(smsc);
    return 0;

error:
    smscenter_unlock(smsc);
    return -1;
}

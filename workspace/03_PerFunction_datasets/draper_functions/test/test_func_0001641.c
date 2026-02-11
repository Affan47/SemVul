ois_submit_msg(SMSCenter *smsc, const Msg *msg)
{
    int ret;

    ois_debug_level = smsc->ois_flags & OIS_FLAG_DEBUG;
    SAY(2, "ois_submit_msg");
    ois_swap_buffering(smsc);

    if (msg_type((Msg *)msg) != sms) {
	error(0, "ois_submit_msg: can not handle message types other than smart_msg");
	goto error;
    }

    if (smsc->socket == -1) {
	ret = ois_open_sender(smsc);
	if (ret < 0) {
	    goto error;
	}
    }

    ret = ois_submit_sm_invoke(smsc, msg);
    if (ret < 0) {
	goto error_close;
    }

    ++smsc->ois_ack_debt;
    time(&smsc->ois_alive);
    ret = 0;
    goto out;

 error_close:
    if (smsc->ois_ack_debt != 0) {
	warning(0, "ois_submit_msg: missing %d ack(s)...",
		smsc->ois_ack_debt);
    }
    SAY(4, "ois_submit_msg: ois_disconnect in error_close");
    ois_disconnect(smsc);
 error:
    SAY(2, "ois_submit_msg error");
    ret = -1;
 out:
    ois_swap_buffering(smsc);
    return ret;
}

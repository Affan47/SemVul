cyz_handle_cmd(struct cyclades_card *cinfo)
{
	struct BOARD_CTRL __iomem *board_ctrl = cinfo->board_ctrl;
	struct cyclades_port *info;
	__u32 channel, param, fw_ver;
	__u8 cmd;
	int special_count;
	int delta_count;

	fw_ver = readl(&board_ctrl->fw_version);

	while (cyz_fetch_msg(cinfo, &channel, &cmd, &param) == 1) {
		special_count = 0;
		delta_count = 0;
		info = &cinfo->ports[channel];

		switch (cmd) {
		case C_CM_PR_ERROR:
			tty_insert_flip_char(&info->port, 0, TTY_PARITY);
			info->icount.rx++;
			special_count++;
			break;
		case C_CM_FR_ERROR:
			tty_insert_flip_char(&info->port, 0, TTY_FRAME);
			info->icount.rx++;
			special_count++;
			break;
		case C_CM_RXBRK:
			tty_insert_flip_char(&info->port, 0, TTY_BREAK);
			info->icount.rx++;
			special_count++;
			break;
		case C_CM_MDCD:
			info->icount.dcd++;
			delta_count++;
			if (info->port.flags & ASYNC_CHECK_CD) {
				u32 dcd = fw_ver > 241 ? param :
					readl(&info->u.cyz.ch_ctrl->rs_status);
				if (dcd & C_RS_DCD)
					wake_up_interruptible(&info->port.open_wait);
				else
					tty_port_tty_hangup(&info->port, false);
			}
			break;
		case C_CM_MCTS:
			info->icount.cts++;
			delta_count++;
			break;
		case C_CM_MRI:
			info->icount.rng++;
			delta_count++;
			break;
		case C_CM_MDSR:
			info->icount.dsr++;
			delta_count++;
			break;
#ifdef Z_WAKE
		case C_CM_IOCTLW:
			complete(&info->shutdown_wait);
			break;
#endif
#ifdef CONFIG_CYZ_INTR
		case C_CM_RXHIWM:
		case C_CM_RXNNDT:
		case C_CM_INTBACK2:

#ifdef CY_DEBUG_INTERRUPTS
			printk(KERN_DEBUG "cyz_interrupt: rcvd intr, card %d, "
					"port %ld\n", info->card, channel);
#endif
			cyz_handle_rx(info);
			break;
		case C_CM_TXBEMPTY:
		case C_CM_TXLOWWM:
		case C_CM_INTBACK:

#ifdef CY_DEBUG_INTERRUPTS
			printk(KERN_DEBUG "cyz_interrupt: xmit intr, card %d, "
					"port %ld\n", info->card, channel);
#endif
			cyz_handle_tx(info);
			break;
#endif
		case C_CM_FATAL:

			break;
		default:
			break;
		}
		if (delta_count)
			wake_up_interruptible(&info->port.delta_msr_wait);
		if (special_count)
			tty_schedule_flip(&info->port);
	}
}

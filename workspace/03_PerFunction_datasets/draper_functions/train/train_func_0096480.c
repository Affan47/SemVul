dwc3_send_gadget_generic_command(struct dwc3 *dwc, unsigned cmd, u32 param)
{
	u32		timeout = 500;
	u32		reg;

	trace_dwc3_gadget_generic_cmd(cmd, param);

	dwc3_writel(dwc->regs, DWC3_DGCMDPAR, param);
	dwc3_writel(dwc->regs, DWC3_DGCMD, cmd | DWC3_DGCMD_CMDACT);

	do {
		reg = dwc3_readl(dwc->regs, DWC3_DGCMD);
		if (!(reg & DWC3_DGCMD_CMDACT)) {
			dwc3_trace(trace_dwc3_gadget,
					"Command Complete --> %d",
					DWC3_DGCMD_STATUS(reg));
			if (DWC3_DGCMD_STATUS(reg))
				return -EINVAL;
			return 0;
		}


		timeout--;
		if (!timeout) {
			dwc3_trace(trace_dwc3_gadget,
					"Command Timed Out");
			return -ETIMEDOUT;
		}
		udelay(1);
	} while (1);
}

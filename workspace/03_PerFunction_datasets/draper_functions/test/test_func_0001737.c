handle_cop0(UINT32 op)
{
	if ((SR & SR_KSU_MASK) != SR_KSU_KERNEL && !(SR & SR_COP0))
		generate_exception(EXCEPTION_BADCOP, 1);

	switch (RSREG)
	{
		case 0x00:			if (RTREG) RTVAL64 = (INT32)get_cop0_reg(RDREG);		break;
		case 0x01:			if (RTREG) RTVAL64 = get_cop0_reg(RDREG);				break;
		case 0x02:			if (RTREG) RTVAL64 = (INT32)get_cop0_creg(RDREG);		break;
		case 0x04:			set_cop0_reg(RDREG, RTVAL32);							break;
		case 0x05:			set_cop0_reg(RDREG, RTVAL64);							break;
		case 0x06:			set_cop0_creg(RDREG, RTVAL32);							break;
		case 0x08:
			switch (RTREG)
			{
				case 0x00:		if (!mips3.cf[0]) ADDPC(SIMMVAL);					break;
				case 0x01:		if (mips3.cf[0]) ADDPC(SIMMVAL);					break;
				case 0x02:		invalid_instruction(op);							break;
				case 0x03:		invalid_instruction(op);							break;
				default:	invalid_instruction(op);										break;
			}
			break;
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1a:
		case 0x1b:
		case 0x1c:
		case 0x1d:
		case 0x1e:
		case 0x1f:
			switch (op & 0x01ffffff)
			{
				case 0x01:															break;
				case 0x02:		logtlbentry();										break;
				case 0x06:		logtlbentry();										break;
				case 0x08:															break;
				case 0x10:		invalid_instruction(op);							break;
				case 0x18:		logerror("ERET\n"); mips3.pc = mips3.cpr[0][COP0_EPC]; SR &= ~SR_EXL; check_irqs();	break;
				default:	invalid_instruction(op);										break;
			}
			break;
		default:	invalid_instruction(op);												break;
	}
}

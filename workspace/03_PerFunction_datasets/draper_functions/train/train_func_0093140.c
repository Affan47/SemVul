tms32025_get_reg(int regnum)
{
	switch (regnum)
	{
		case REG_PC:
		case TMS32025_PC: return R.PC;

		case REG_SP:
		case TMS32025_STK7:  return R.STACK[7];
		case TMS32025_STK6:  return R.STACK[6];
		case TMS32025_STK5:  return R.STACK[5];
		case TMS32025_STK4:  return R.STACK[4];
		case TMS32025_STK3:  return R.STACK[3];
		case TMS32025_STK2:  return R.STACK[2];
		case TMS32025_STK1:  return R.STACK[1];
		case TMS32025_STK0:  return R.STACK[0];
		case TMS32025_STR0:  return R.STR0;
		case TMS32025_STR1:  return R.STR1;
		case TMS32025_IFR:   return R.IFR;
		case TMS32025_RPTC:  return R.RPTC;
		case TMS32025_ACC:   return R.ACC.d;
		case TMS32025_PREG:  return R.Preg.d;
		case TMS32025_TREG:  return R.Treg;
		case TMS32025_AR0:   return R.AR[0];
		case TMS32025_AR1:   return R.AR[1];
		case TMS32025_AR2:   return R.AR[2];
		case TMS32025_AR3:   return R.AR[3];
		case TMS32025_AR4:   return R.AR[4];
		case TMS32025_AR5:   return R.AR[5];
		case TMS32025_AR6:   return R.AR[6];
		case TMS32025_AR7:   return R.AR[7];
		case TMS32025_DRR:   return M_RDRAM(0);
		case TMS32025_DXR:   return M_RDRAM(1);
		case TMS32025_TIM:   return M_RDRAM(2);
		case TMS32025_PRD:   return M_RDRAM(3);
		case TMS32025_IMR:   return M_RDRAM(4);
		case TMS32025_GREG:  return M_RDRAM(5);
		case REG_PREVIOUSPC: return R.PREVPC;
		default:
			if (regnum <= REG_SP_CONTENTS)
			{
				unsigned offset = (REG_SP_CONTENTS - regnum);
				if (offset < 8)
					return R.STACK[offset];
			}
	}
	return 0;
}

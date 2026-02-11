m6502_set_reg (int regnum, unsigned val)
{
	switch( regnum )
	{
		case REG_PC: PCW = val; change_pc16(PCD); break;
		case M6502_PC: m6502.pc.w.l = val; break;
		case REG_SP: S = val; break;
		case M6502_S: m6502.sp.b.l = val; break;
		case M6502_P: m6502.p = val; break;
		case M6502_A: m6502.a = val; break;
		case M6502_X: m6502.x = val; break;
		case M6502_Y: m6502.y = val; break;
		case M6502_EA: m6502.ea.w.l = val; break;
		case M6502_ZP: m6502.zp.w.l = val; break;
		case M6502_NMI_STATE: m6502_set_irq_line( IRQ_LINE_NMI, val ); break;
		case M6502_IRQ_STATE: m6502_set_irq_line( 0, val ); break;
		case M6502_SO_STATE: m6502_set_irq_line( M6502_SET_OVERFLOW, val ); break;
		default:
			if( regnum <= REG_SP_CONTENTS )
			{
				unsigned offset = S + 2 * (REG_SP_CONTENTS - regnum);
				if( offset < 0x1ff )
				{
					WRMEM( offset, val & 0xfff );
					WRMEM( offset + 1, (val >> 8) & 0xff );
				}
			}
	}
}

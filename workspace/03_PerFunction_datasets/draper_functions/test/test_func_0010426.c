HandleBranch(  data32_t insn )
{
	data32_t off = (insn & INSN_BRANCH) << 2;


	if (insn & INSN_BL)
	{
		SetRegister(14,R15 + 4);
	}


	if (off & 0x2000000u)
	{
		R15 -= ((~(off | 0xfc000000u)) + 1) - 8;
	}
	else
	{
		R15 += off + 8;
	}
}

cpu_read32( int addr )
{
	data32_t result = cpu_readmem26ledw_dword(addr&ADDRESS_MASK);


	if (addr&3) {
		if (ARM_DEBUG_CORE && addr&1)
			logerror("%08x: Unaligned byte read %08x\n",R15,addr);

		if ((addr&3)==3)
			return ((result&0x000000ff)<<24)|((result&0xffffff00)>> 8);
		if ((addr&3)==2)
			return ((result&0x0000ffff)<<16)|((result&0xffff0000)>>16);
		if ((addr&3)==1)
			return ((result&0x00ffffff)<< 8)|((result&0xff000000)>>24);
	}

	return result;
}

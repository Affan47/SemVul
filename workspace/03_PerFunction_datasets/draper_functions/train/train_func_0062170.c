handleWrite(uaecptr addr, uae_u8 value)
{
	D(bug("acia: Write 0x%02x to 0x%08x",value,addr));

	switch(addr-getHWoffset()) {
		case 0:
			if ((value & ACIA_CR_PREDIV_MASK)==ACIA_CR_RESET) {
				ACIA::reset();
			} else {
				WriteControl(value);
			}
			break;
		case 2:
			WriteData(value);
			break;
	}
}

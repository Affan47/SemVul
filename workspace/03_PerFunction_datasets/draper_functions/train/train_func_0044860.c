CARTRIDGE_BountyBob2(UWORD addr)
{
	if (Atari800_machine_type == Atari800_MACHINE_5200) {
		if (addr >= 0x5ff6 && addr <= 0x5ff9) {
			addr -= 0x5ff6;
			MEMORY_CopyROM(0x5000, 0x5fff, active_cart->image + 0x4000 + addr * 0x1000);
			active_cart->state = (active_cart->state & 0x03) | (addr << 2);
		}
	}
	else {
		if (addr >= 0x9ff6 && addr <= 0x9ff9) {
			addr -= 0x9ff6;
			MEMORY_CopyROM(0x9000, 0x9fff, active_cart->image + 0x4000 + addr * 0x1000);
			active_cart->state = (active_cart->state & 0x03) | (addr << 2);
		}
	}
}

snd_wm8766_write(struct snd_wm8766 *wm, u16 addr, u16 data)
{
	if (addr < WM8766_REG_COUNT)
		wm->regs[addr] = data;
	wm->ops.write(wm, addr, data);
}

mem_write_default(Uint16 adr,Uint8 v)
{
  Uint8 bk;

  if (adr>=0xfe00 && adr<0xfea0) {
    oam_space[adr-0xfe00]=v;
    return;
  }

  if (adr>=0xfea0 && adr<0xff00) {
    himem[adr-0xfea0]=v;
    return;
  }

  if (adr>=0xff00) {
    mem_write_ff(adr,v);
    return;
  }

  if (adr>=0xe000 && adr<0xfe00) adr-=0x2000;

  bk=(adr&0xf000)>>12;
  switch(bk) {
  case 0:
  case 1:
    if ((v&0x0f)==0x0a) enable_ram();
    else disable_ram();
    return;

  case 2:
  case 3:select_rom_page(adr,v);return;
  case 4:
  case 5:
    if (rom_type&MBC1) {
      if (mbc1_mem_mode==MBC1_16_8_MEM_MODE)
	mbc1_line=v&0x03;
      else set_active_ram_page(v);
      return;
    }
    else set_active_ram_page(v);

    if (rom_type&RUMBLE && conf.rumble_on && v&0x08) rb_on=1;

    if (rom_type&TIMER) {
      rom_timer->reg_sel=v&0x0f;

    }
    return;
  case 6:
  case 7:
    if (rom_type&MBC1) {
      if (!v) mbc1_mem_mode=MBC1_16_8_MEM_MODE;
      else if (v==1) mbc1_mem_mode=MBC1_4_32_MEM_MODE;
      return;
    }
    if (rom_type&TIMER) {
      if (!rom_timer->latch && v) rom_timer_lock();
      rom_timer->latch=v;
    }
    return;
  case 8:
  case 9:vram_page[active_vram_page][adr-0x8000]=v;return;
  case 0xa:
  case 0xb:
    if (!ram_enable) return;
    if (rom_type&TIMER && rom_timer->reg_sel&0x08) {
      rom_timer_write(v);
      return;
    }
    ram_page[active_ram_page][adr-0xa000]=v;
    return;
  case 0xc:wram_page[0][adr-0xc000]=v;return;
  case 0xd:wram_page[active_wram_page][adr-0xd000]=v;return;
  }
}

data_initial()
{
  rhythm = buf_addr[2];
  mus_block = (buf_addr[0x0D]<<8)+buf_addr[0x0C];
  ins_block = (buf_addr[0x09]<<8)+buf_addr[0x08];
  I = mus_block+1;
  if(rhythm != 0)
    {


      ad_a0b0l_reg_(8,0x18,0);
      ad_a0b0l_reg_(7,0x1F,0);
    }
  bd_modify = 0;

  band = 0; music_on = 1;
}

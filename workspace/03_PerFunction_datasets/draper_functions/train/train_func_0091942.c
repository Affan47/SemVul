playnote(unsigned char chan)
{
  unsigned char oplchan = set_opl_chip(chan);
  unsigned char op = op_table[oplchan], insnr = channel[chan].inst;

  if(!(flags & NoKeyOn))
    opl->write(0xb0 + oplchan, 0);


  opl->write(0x20 + op, inst[insnr].data[1]);
  opl->write(0x23 + op, inst[insnr].data[2]);
  opl->write(0x60 + op, inst[insnr].data[3]);
  opl->write(0x63 + op, inst[insnr].data[4]);
  opl->write(0x80 + op, inst[insnr].data[5]);
  opl->write(0x83 + op, inst[insnr].data[6]);
  opl->write(0xe0 + op, inst[insnr].data[7]);
  opl->write(0xe3 + op, inst[insnr].data[8]);
  opl->write(0xc0 + oplchan, inst[insnr].data[0]);
  opl->write(0xbd, inst[insnr].misc);


  channel[chan].key = 1;
  setfreq(chan);

  if (flags & Faust) {
    channel[chan].vol2 = 63;
    channel[chan].vol1 = 63;
  }
  setvolume(chan);
}

Create(DiskFile      *_diskfile,
                            u64            _offset,
                            u64            _blocksize,
                            u32            _exponent,
                            const MD5Hash &_setid)
{
  diskfile = _diskfile;
  offset = _offset;


  packet.header.magic  = packet_magic;
  packet.header.length = sizeof(packet) + _blocksize;

  packet.header.setid  = _setid;
  packet.header.type   = recoveryblockpacket_type;
  packet.exponent      = _exponent;


  packetcontext = new MD5Context;
  packetcontext->Update(&packet.header.setid,
                        sizeof(RECOVERYBLOCKPACKET)-offsetof(RECOVERYBLOCKPACKET, header.setid));


  datablock.SetLocation(_diskfile, _offset + sizeof(packet));
  datablock.SetLength(_blocksize);
}

createStubFunction(uint8_t *Addr,
                                             unsigned AbiVariant) {
  if (Arch == Triple::aarch64 || Arch == Triple::aarch64_be) {


    writeBytesUnaligned(0xd2e00010, Addr,    4);
    writeBytesUnaligned(0xf2c00010, Addr+4,  4);
    writeBytesUnaligned(0xf2a00010, Addr+8,  4);
    writeBytesUnaligned(0xf2800010, Addr+12, 4);
    writeBytesUnaligned(0xd61f0200, Addr+16, 4);

    return Addr;
  } else if (Arch == Triple::arm || Arch == Triple::armeb) {


    writeBytesUnaligned(0xe51ff004, Addr, 4);
    return Addr + 4;
  } else if (IsMipsO32ABI) {


    const unsigned LuiT9Instr = 0x3c190000, AdduiT9Instr = 0x27390000;
    const unsigned JrT9Instr = 0x03200008, NopInstr = 0x0;

    writeBytesUnaligned(LuiT9Instr, Addr, 4);
    writeBytesUnaligned(AdduiT9Instr, Addr+4, 4);
    writeBytesUnaligned(JrT9Instr, Addr+8, 4);
    writeBytesUnaligned(NopInstr, Addr+12, 4);
    return Addr;
  } else if (Arch == Triple::ppc64 || Arch == Triple::ppc64le) {


    writeInt32BE(Addr,    0x3D800000);
    writeInt32BE(Addr+4,  0x618C0000);
    writeInt32BE(Addr+8,  0x798C07C6);
    writeInt32BE(Addr+12, 0x658C0000);
    writeInt32BE(Addr+16, 0x618C0000);
    if (AbiVariant == 2) {


      writeInt32BE(Addr+20, 0xF8410018);
      writeInt32BE(Addr+24, 0x7D8903A6);
      writeInt32BE(Addr+28, 0x4E800420);
    } else {


      writeInt32BE(Addr+20, 0xF8410028);
      writeInt32BE(Addr+24, 0xE96C0000);
      writeInt32BE(Addr+28, 0xE84C0008);
      writeInt32BE(Addr+32, 0x7D6903A6);
      writeInt32BE(Addr+36, 0xE96C0010);
      writeInt32BE(Addr+40, 0x4E800420);
    }
    return Addr;
  } else if (Arch == Triple::systemz) {
    writeInt16BE(Addr,    0xC418);
    writeInt16BE(Addr+2,  0x0000);
    writeInt16BE(Addr+4,  0x0004);
    writeInt16BE(Addr+6,  0x07F1);

    return Addr;
  } else if (Arch == Triple::x86_64) {
    *Addr      = 0xFF;
    *(Addr+1)  = 0x25;

  } else if (Arch == Triple::x86) {
    *Addr      = 0xE9;
  }
  return Addr;
}

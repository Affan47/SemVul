construct(dspic::dsPicProcessor *new_cpu,
					    unsigned int new_mode,
					    unsigned int addr)
  {

    switch (new_mode&7) {

    case eDirect:
      return new RegDirectAddrMode(new_cpu, addr);
    case eIndirect:
      return new RegIndirectAddrMode(new_cpu, addr);
    case eIndirectPostDec:
      return new RegIndirectPostDecAddrMode(new_cpu, addr);
    case eIndirectPostInc:
      return new RegIndirectPostIncAddrMode(new_cpu, addr);
    case eIndirectPreDec:
      return new RegIndirectPreDecAddrMode(new_cpu, addr);
    case eIndirectPreInc:
      return new RegIndirectPreIncAddrMode(new_cpu, addr);


      break;
    case eLiteral:
    case eLiteral_:
      return new LiteralAddressingMode(new_cpu, addr&0x1f);
    }

    return 0;
  }

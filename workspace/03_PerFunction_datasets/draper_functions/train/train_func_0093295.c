createX86ELFObjectWriter(raw_pwrite_stream &OS,
                                               bool IsELF64, uint8_t OSABI,
                                               uint16_t EMachine) {
  MCELFObjectTargetWriter *MOTW =
    new X86ELFObjectWriter(IsELF64, OSABI, EMachine);
  return createELFObjectWriter(MOTW, OS,  true);
}

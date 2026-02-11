createAArch64MachObjectWriter(raw_pwrite_stream &OS,
                                                    uint32_t CPUType,
                                                    uint32_t CPUSubtype) {
  return createMachObjectWriter(
      new AArch64MachObjectWriter(CPUType, CPUSubtype), OS,
      true);
}

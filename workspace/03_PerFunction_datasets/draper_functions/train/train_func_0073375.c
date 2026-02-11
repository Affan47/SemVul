isMachO() const {
    return Triple(M->getTargetTriple()).isOSBinFormatMachO();
  }

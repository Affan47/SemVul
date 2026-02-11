getArchTypeName(ArchType Kind) {
  switch (Kind) {
  case UnknownArch: return "unknown";

  case aarch64:     return "aarch64";
  case aarch64_be:  return "aarch64_be";
  case arm:         return "arm";
  case armeb:       return "armeb";
  case avr:         return "avr";
  case bpfel:       return "bpfel";
  case bpfeb:       return "bpfeb";
  case hexagon:     return "hexagon";
  case mips:        return "mips";
  case mipsel:      return "mipsel";
  case mips64:      return "mips64";
  case mips64el:    return "mips64el";
  case msp430:      return "msp430";
  case ppc64:       return "powerpc64";
  case ppc64le:     return "powerpc64le";
  case ppc:         return "powerpc";
  case r600:        return "r600";
  case amdgcn:      return "amdgcn";
  case sparc:       return "sparc";
  case sparcv9:     return "sparcv9";
  case sparcel:     return "sparcel";
  case systemz:     return "s390x";
  case tce:         return "tce";
  case thumb:       return "thumb";
  case thumbeb:     return "thumbeb";
  case x86:         return "i386";
  case x86_64:      return "x86_64";
  case xcore:       return "xcore";
  case nvptx:       return "nvptx";
  case nvptx64:     return "nvptx64";
  case le32:        return "le32";
  case le64:        return "le64";
  case amdil:       return "amdil";
  case amdil64:     return "amdil64";
  case hsail:       return "hsail";
  case hsail64:     return "hsail64";
  case spir:        return "spir";
  case spir64:      return "spir64";
  case kalimba:     return "kalimba";
  case shave:       return "shave";
  case wasm32:      return "wasm32";
  case wasm64:      return "wasm64";
  }

  llvm_unreachable("Invalid ArchType!");
}

adjustFixupValue(unsigned Kind, uint64_t Value) {
  switch (Kind) {
  default:
    llvm_unreachable("Unknown fixup kind!");
  case FK_Data_1:
  case FK_Data_2:
  case FK_Data_4:
  case FK_Data_8:
    return Value;

  case Sparc::fixup_sparc_wplt30:
  case Sparc::fixup_sparc_call30:
    return (Value >> 2) & 0x3fffffff;

  case Sparc::fixup_sparc_br22:
    return (Value >> 2) & 0x3fffff;

  case Sparc::fixup_sparc_br19:
    return (Value >> 2) & 0x7ffff;

  case Sparc::fixup_sparc_br16_2:
    return (Value >> 2) & 0xc000;

  case Sparc::fixup_sparc_br16_14:
    return (Value >> 2) & 0x3fff;

  case Sparc::fixup_sparc_pc22:
  case Sparc::fixup_sparc_got22:
  case Sparc::fixup_sparc_tls_gd_hi22:
  case Sparc::fixup_sparc_tls_ldm_hi22:
  case Sparc::fixup_sparc_tls_ie_hi22:
  case Sparc::fixup_sparc_hi22:
    return (Value >> 10) & 0x3fffff;

  case Sparc::fixup_sparc_pc10:
  case Sparc::fixup_sparc_got10:
  case Sparc::fixup_sparc_tls_gd_lo10:
  case Sparc::fixup_sparc_tls_ldm_lo10:
  case Sparc::fixup_sparc_tls_ie_lo10:
  case Sparc::fixup_sparc_lo10:
    return Value & 0x3ff;

  case Sparc::fixup_sparc_tls_ldo_hix22:
  case Sparc::fixup_sparc_tls_le_hix22:
    return (~Value >> 10) & 0x3fffff;

  case Sparc::fixup_sparc_tls_ldo_lox10:
  case Sparc::fixup_sparc_tls_le_lox10:
    return (~(~Value & 0x3ff)) & 0x1fff;

  case Sparc::fixup_sparc_h44:
    return (Value >> 22) & 0x3fffff;

  case Sparc::fixup_sparc_m44:
    return (Value >> 12) & 0x3ff;

  case Sparc::fixup_sparc_l44:
    return Value & 0xfff;

  case Sparc::fixup_sparc_hh:
    return (Value >> 42) & 0x3fffff;

  case Sparc::fixup_sparc_hm:
    return (Value >> 32) & 0x3ff;

  case Sparc::fixup_sparc_tls_gd_add:
  case Sparc::fixup_sparc_tls_gd_call:
  case Sparc::fixup_sparc_tls_ldm_add:
  case Sparc::fixup_sparc_tls_ldm_call:
  case Sparc::fixup_sparc_tls_ldo_add:
  case Sparc::fixup_sparc_tls_ie_ld:
  case Sparc::fixup_sparc_tls_ie_ldx:
  case Sparc::fixup_sparc_tls_ie_add:
    return 0;
  }
}

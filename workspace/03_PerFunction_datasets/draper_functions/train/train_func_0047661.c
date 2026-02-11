DetectX86FamilyModel(unsigned EAX, unsigned &Family, unsigned &Model) {
  Family = (EAX >> 8) & 0xf;
  Model  = (EAX >> 4) & 0xf;
  if (Family == 6 || Family == 0xf) {
    if (Family == 0xf)

      Family += (EAX >> 20) & 0xff;

    Model += ((EAX >> 16) & 0xf) << 4;
  }
}

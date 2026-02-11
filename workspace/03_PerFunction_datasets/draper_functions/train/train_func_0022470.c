mode_from_str (const char *str)
{
    if (strncmp (str, "Dreg", 4) == 0) return Dreg;
    if (strncmp (str, "Areg", 4) == 0) return Areg;
    if (strncmp (str, "Aind", 4) == 0) return Aind;
    if (strncmp (str, "Apdi", 4) == 0) return Apdi;
    if (strncmp (str, "Aipi", 4) == 0) return Aipi;
    if (strncmp (str, "Ad16", 4) == 0) return Ad16;
    if (strncmp (str, "Ad8r", 4) == 0) return Ad8r;
    if (strncmp (str, "absw", 4) == 0) return absw;
    if (strncmp (str, "absl", 4) == 0) return absl;
    if (strncmp (str, "PC16", 4) == 0) return PC16;
    if (strncmp (str, "PC8r", 4) == 0) return PC8r;
    if (strncmp (str, "Immd", 4) == 0) return imm;
    abort ();
    return (amodes)0;
}

toString()
  {
    gint64 i64;
    get(i64);
    int i = i64 &0xfff;

    char buff[256];

    const char *OSCdesc[] = {
      "LP oscillator",
      "XT oscillator",
      "HS oscillator",
      "RC oscillator",
      "EC oscillator w/ OSC2 configured as divide-by-4 clock output",
      "EC oscillator w/ OSC2 configured as RA6",
      "HS oscillator with PLL enabled/Clock frequency = (4 x FOSC)",
      "RC oscillator w/ OSC2 configured as RA6",
      "Internal oscillator block, port function on RA6 and RA7",
      "Internal oscillator block, CLKO function on RA6, port function on RA7",
      "External RC oscillator, CLKO function on RA6",
      "External RC oscillator, CLKO function on RA6",
      "External RC oscillator, CLKO function on RA6",
      "External RC oscillator, CLKO function on RA6",
      "External RC oscillator, CLKO function on RA6",
      "External RC oscillator, CLKO function on RA6"
    };
    snprintf(buff,sizeof(buff),
             "$%04x\n"
             " FOSC=%d - Clk source = %s\n"
             " OSCEN=%d - Oscillator switching is %s\n",
             i,
             i&(FOSC0|FOSC1|FOSC2|FOSC3), OSCdesc[i&(FOSC0|FOSC1|FOSC2|FOSC3)],
             (i&OSCEN?1:0), ((i&OSCEN) ? "disabled" : "enabled"));

    return string(buff);
  }

print_synth_cyrix(const char*   name,
                  unsigned int  val)
{
   printf("%s", name);
   START;
   FM (0,4,  0,4,     "Cyrix Media GX / GXm");
   FM (0,4,  0,9,     "Cyrix 5x86");
   F  (0,4,           "Cyrix 5x86 (unknown model)");
   FM (0,5,  0,2,     "Cyrix M1 6x86");
   FM (0,5,  0,4,     "Cyrix M1 WinChip (C6)");
   FM (0,5,  0,8,     "Cyrix M1 WinChip 2 (C6-2)");
   FM (0,5,  0,9,     "Cyrix M1 WinChip 3 (C6-2)");
   F  (0,5,           "Cyrix M1 (unknown model)");
   FM (0,6,  0,0,     "Cyrix M2 6x86MX");
   FM (0,6,  0,5,     "Cyrix M2");
   F  (0,6,           "Cyrix M2 (unknown model)");
   DEFAULT           ("unknown");
   printf("\n");
}

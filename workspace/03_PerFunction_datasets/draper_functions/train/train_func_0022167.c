print_synth_nsc(const char*   name,
                unsigned int  val)
{
   printf("%s", name);
   START;
   FM (0,5,  0,4,     "NSC Geode GX1/GXLV/GXm");
   FM (0,5,  0,5,     "NSC Geode GX2");
   F  (0,5,           "NSC Geode (unknown model)");
   DEFAULT           ("unknown");
   printf("\n");
}

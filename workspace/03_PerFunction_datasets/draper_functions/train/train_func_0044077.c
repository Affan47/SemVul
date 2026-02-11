print_synth_sis(const char*   name,
                unsigned int  val)
{
   printf("%s", name);
   START;
   FM (0,5,  0,0,     "SiS 55x");
   DEFAULT           ("unknown");
   printf("\n");
}

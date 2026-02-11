setOptimizedMethods (PluginInfo * p)
{
#ifdef HAVE_ORC
  unsigned int cpuFlavour =
      orc_target_get_default_flags (orc_target_get_by_name ("mmx"));
#else
  unsigned int cpuFlavour = 0;
#endif


  p->methods.draw_line = draw_line;
  p->methods.zoom_filter = zoom_filter_c;


  GST_INFO ("orc cpu flags: 0x%08x", cpuFlavour);


#ifdef HAVE_CPU_I386
#ifdef HAVE_MMX
#ifdef HAVE_ORC
  GST_INFO ("have an x86");
  if (cpuFlavour & ORC_TARGET_MMX_MMXEXT) {
    GST_INFO ("Extended MMX detected. Using the fastest methods!");
    p->methods.draw_line = draw_line_xmmx;
    p->methods.zoom_filter = zoom_filter_xmmx;
  } else if (cpuFlavour & ORC_TARGET_MMX_MMX) {
    GST_INFO ("MMX detected. Using fast methods!");
    p->methods.draw_line = draw_line_mmx;
    p->methods.zoom_filter = zoom_filter_mmx;
  } else {
    GST_INFO ("Too bad ! No SIMD optimization available for your CPU.");
  }
#endif
#endif
#endif


#if 0
#ifdef HAVE_CPU_PPC64
  if ((cpuFlavour & CPU_OPTION_64_BITS) != 0) {

    p->methods.zoom_filter = ppc_zoom_generic;
  }
#endif

#ifdef HAVE_CPU_PPC
  if ((cpuFlavour & ORC_TARGET_ALTIVEC_ALTIVEC) != 0) {

    p->methods.zoom_filter = ppc_zoom_G4;
  } else {

    p->methods.zoom_filter = ppc_zoom_generic;
  }
#endif
#endif

  cpuFlavour = 0;
}

swe_close(void)
{
  int i;

  for (i = 0; i < SEI_NEPHFILES; i ++) {
    if (swed.fidat[i].fptr != NULL)
      fclose(swed.fidat[i].fptr);
    memset((void *) &swed.fidat[i], 0, sizeof(struct file_data));
  }

  for (i = 0; i < SEI_NPLANETS; i++) {
    if (swed.pldat[i].segp != NULL) {
      free((void *) swed.pldat[i].segp);
    }
    if (swed.pldat[i].refep != NULL) {
      free((void *) swed.pldat[i].refep);
    }
    memset((void *) &swed.pldat[i], 0, sizeof(struct plan_data));
  }

  for (i = 0; i < SEI_NNODE_ETC; i++) {
    memset((void *) &swed.nddat[i], 0, sizeof(struct node_data));
  }
  memset((void *) &swed.oec, 0, sizeof(struct epsilon));
  memset((void *) &swed.oec2000, 0, sizeof(struct epsilon));
  memset((void *) &swed.nut, 0, sizeof(struct nut));
  memset((void *) &swed.nut2000, 0, sizeof(struct nut));
  memset((void *) &swed.nutv, 0, sizeof(struct nut));

#ifndef NO_JPL
  swi_close_jpl_file();
#endif
  swed.jpl_file_is_open = FALSE;

  if (fixfp != NULL) {
    fclose(fixfp);
    fixfp = NULL;
  }
#ifdef TRACE
  swi_open_trace(NULL);
  if (swi_fp_trace_c != NULL) {
    if (swi_trace_count < TRACE_COUNT_MAX) {
      fputs("\n/*SWE_CLOSE*/\n", swi_fp_trace_c);
      fputs("  swe_close();\n", swi_fp_trace_c);
#if 0
      fputs("}\n", swi_fp_trace_c);
#endif
    }
#if 0
    fclose(swi_fp_trace_c);
#endif
  }
#if 0
  if (swi_fp_trace_out != NULL)
    fclose(swi_fp_trace_out);
  swi_fp_trace_c = NULL;
  swi_fp_trace_out = NULL;
#endif
#endif
}

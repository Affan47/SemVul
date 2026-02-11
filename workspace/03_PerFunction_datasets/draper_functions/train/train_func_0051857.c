status_recognition_end(Recog *recog, void *dummy)
{
  if (recog->process_segment) {
    if (verbose_flag) {
      printf("Segmented by short pause, continue to next...\n");
    } else {

    }
  }
  if (recog->jconf->decodeopt.segment) {
    if (have_progout) {
      if (confwordnum > 0) {
	printf("\n");
      }
    }
  }
}

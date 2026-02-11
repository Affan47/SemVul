j_request_terminate(Recog *recog)
{


  if (recog->process_active) {
    recog->process_want_terminate = TRUE;
    recog->process_want_reload = TRUE;
    recog->process_active = FALSE;
  }
  if (recog->jconf->input.type == INPUT_WAVEFORM) {
    if (recog->adin->ad_terminate != NULL) {

      (*(recog->adin->ad_terminate))();
    }
  } else {

    if (recog->jconf->input.speech_input == SP_MFCMODULE) {
      if (recog->mfcclist->func.fv_terminate) recog->mfcclist->func.fv_terminate();
    }
  }
}

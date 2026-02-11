main ()
{
  uint_t i = 0;
  uint_t win_s = 1024;
  fvec_t * in = new_fvec (win_s);
  fvec_t * out = new_fvec (win_s / 4);


  aubio_beattracking_t * tempo  = new_aubio_beattracking(win_s, 256, 44100);

  smpl_t bpm, confidence;

  while (i < 10) {


    aubio_beattracking_do(tempo,in,out);


    bpm = aubio_beattracking_get_bpm(tempo);
    confidence = aubio_beattracking_get_confidence(tempo);
    fprintf(stderr, "found bpm %f with confidence %f\n", bpm, confidence);
    i++;
  };

  del_aubio_beattracking(tempo);
  del_fvec(in);
  del_fvec(out);
  aubio_cleanup();

  return 0;
}

fs_encdec_test (int samplerate, int channels, int format, int interleave,
                int blocksize)
{
  FS_EncDec * ed;
  char msg[128];
  int i;
  long expected_frames;

  snprintf (msg, 128,
            "+ %2d channel %6d Hz %s, %d frame buffer (%s)",
            channels, samplerate,
            format == FISH_SOUND_VORBIS ? "Vorbis" : (format == FISH_SOUND_FLAC ? "Flac" : "Speex"),
            blocksize,
            interleave ? "interleave" : "non-interleave");
  INFO (msg);

  ed = fs_encdec_new (samplerate, channels, format, interleave, blocksize);

#if 0
  fish_sound_comment_add_byname (ed->encoder, "Encoder", "encdec-audio");
  fish_sound_comment_add_byname (ed->encoder, "Format", msg);
#endif

  for (i = 0; i < iter; i++) {
    ed->actual_frames_in += blocksize;
    fish_sound_prepare_truncation (ed->encoder, ed->actual_frames_in,
                                   (i == (iter - 1)));
    fish_sound_encode (ed->encoder, ed->pcm, blocksize);
    ed->reported_frames_in = fish_sound_get_frameno (ed->encoder);
  }

  fish_sound_flush (ed->encoder);
  fish_sound_flush (ed->decoder);
  ed->reported_frames_in = fish_sound_get_frameno (ed->encoder);

  expected_frames = ed->actual_frames_in;
  if (format == FISH_SOUND_SPEEX) {
    expected_frames += (320 - (expected_frames % 320));
  }

  if (ed->actual_frames_out != expected_frames) {
    snprintf (msg, 128,
              "%ld frames encoded, %ld frames decoded",
              ed->actual_frames_in, ed->actual_frames_out);
    if (ed->actual_frames_out < ed->actual_frames_in) {
      FAIL (msg);
    } else {
      WARN (msg);
    }
  }

  expected_frames = ed->reported_frames_in;
  if (format == FISH_SOUND_SPEEX) {
    expected_frames += (320 - (expected_frames % 320));
  }

  if (ed->reported_frames_out != expected_frames) {
    snprintf (msg, 128,
              "%ld frames reported in, %ld frames reported out",
              ed->reported_frames_in, ed->reported_frames_out);
    WARN (msg);
  }

  fs_encdec_delete (ed);

  return 0;
}

rso_encode(void **ptr,unsigned int samplerate,size_t len,void *data) {
  size_t buflen = sizeof(struct rso_sound)+len;
  struct rso_sound *sound = malloc(buflen);

  if (samplerate>RSO_SAMPLERATE_MAX || samplerate<RSO_SAMPLERATE_MIN) return 0;

  LITTLEENDIAN_SET_WORD(&(sound->format),1);
  BIGENDIAN_SET_WORD(&(sound->databytes),len);
  BIGENDIAN_SET_WORD(&(sound->samplerate),samplerate);
  memcpy(sound->data,data,len);

  *ptr = sound;
  return buflen;
}

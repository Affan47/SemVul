GetFrame(int n, IScriptEnvironment* env)
{

  PVideoFrame
    src = child->GetFrame(n, env),
    sht = 0,
    dst = env->NewVideoFrame(vi);

  const unsigned char
    * srcY = src->GetReadPtr(PLANAR_Y),
    * srcU = src->GetReadPtr(PLANAR_U),
    * srcV = src->GetReadPtr(PLANAR_V),
    * shtY = 0,
    * shtU = 0,
    * shtV = 0;

  unsigned char
    * dstY = dst->GetWritePtr(PLANAR_Y),
    * dstU = dst->GetWritePtr(PLANAR_U),
    * dstV = dst->GetWritePtr(PLANAR_V);

  int
    SRC_PITCH_SAMPLES_Y = src->GetPitch(PLANAR_Y),
    SRC_PITCH_SAMPLES_U = src->GetPitch(PLANAR_U),
    SHT_PITCH_SAMPLES_Y = 0,
    SHT_PITCH_SAMPLES_U = 0,
    DST_PITCH_SAMPLES_Y = dst->GetPitch(PLANAR_Y),
    DST_PITCH_SAMPLES_U = dst->GetPitch(PLANAR_U);

  if (tilesheet) {

    sht = tilesheet->GetFrame(n, env);

    shtY = sht->GetReadPtr(PLANAR_Y);
    shtU = sht->GetReadPtr(PLANAR_U);
    shtV = sht->GetReadPtr(PLANAR_V);

    SHT_PITCH_SAMPLES_Y = sht->GetPitch(PLANAR_Y);
    SHT_PITCH_SAMPLES_U = sht->GetPitch(PLANAR_U);

  }

  if (PLANAR)
    processFramePlanar(
      srcY, srcU, srcV,
      shtY, shtU, shtV,
      dstY, dstU, dstV,
      SRC_PITCH_SAMPLES_Y, SRC_PITCH_SAMPLES_U,
      SHT_PITCH_SAMPLES_Y, SHT_PITCH_SAMPLES_U,
      DST_PITCH_SAMPLES_Y, DST_PITCH_SAMPLES_U,
      env);
  else
    processFramePacked(
      srcY, shtY, dstY,
      SRC_PITCH_SAMPLES_Y, SHT_PITCH_SAMPLES_Y, DST_PITCH_SAMPLES_Y,
      env);

  return dst;

}

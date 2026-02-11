imuCalculateVarianceAndMean(BiasObj* bias, Axis3f* varOut, Axis3f* meanOut)
{
  uint32_t i;
  int64_t sum[GYRO_NBR_OF_AXES] = {0};
  int64_t sumSq[GYRO_NBR_OF_AXES] = {0};

  for (i = 0; i < IMU_NBR_OF_BIAS_SAMPLES; i++)
  {
    sum[0] += bias->buffer[i].x;
    sum[1] += bias->buffer[i].y;
    sum[2] += bias->buffer[i].z;
    sumSq[0] += bias->buffer[i].x * bias->buffer[i].x;
    sumSq[1] += bias->buffer[i].y * bias->buffer[i].y;
    sumSq[2] += bias->buffer[i].z * bias->buffer[i].z;
  }

  varOut->x = (sumSq[0] - ((int64_t)sum[0] * sum[0]) / IMU_NBR_OF_BIAS_SAMPLES);
  varOut->y = (sumSq[1] - ((int64_t)sum[1] * sum[1]) / IMU_NBR_OF_BIAS_SAMPLES);
  varOut->z = (sumSq[2] - ((int64_t)sum[2] * sum[2]) / IMU_NBR_OF_BIAS_SAMPLES);

  meanOut->x = (float)sum[0] / IMU_NBR_OF_BIAS_SAMPLES;
  meanOut->y = (float)sum[1] / IMU_NBR_OF_BIAS_SAMPLES;
  meanOut->z = (float)sum[2] / IMU_NBR_OF_BIAS_SAMPLES;

  isInit = true;
}

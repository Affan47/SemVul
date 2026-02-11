imuAddBiasValue(BiasObj* bias, Axis3i16* dVal)
{
  bias->bufHead->x = dVal->x;
  bias->bufHead->y = dVal->y;
  bias->bufHead->z = dVal->z;
  bias->bufHead++;

  if (bias->bufHead >= &bias->buffer[IMU_NBR_OF_BIAS_SAMPLES])
  {
    bias->bufHead = bias->buffer;
    bias->isBufferFilled = true;
  }
}

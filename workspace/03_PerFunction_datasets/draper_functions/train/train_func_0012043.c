i2cDevGiveSemaphore(CPAL_DevTypeDef CPAL_Dev)
{
  xSemaphoreHandle semaphore = getSemaphore(CPAL_Dev);
  bool isInInterrupt = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;

  if (isInInterrupt) {
    semaphoreGiveFromISR(semaphore);
  } else {
    xSemaphoreGive(semaphore);
  }
}

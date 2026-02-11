CAN_WakeUp(CAN_TypeDef* CANx)
{
  uint32_t wait_slak = SLAK_TIMEOUT;
  uint8_t wakeupstatus = CAN_WakeUp_Failed;


  assert_param(IS_CAN_ALL_PERIPH(CANx));


  CANx->MCR &= ~(uint32_t)CAN_MCR_SLEEP;


  while(((CANx->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK)&&(wait_slak!=0x00))
  {
   wait_slak--;
  }
  if((CANx->MSR & CAN_MSR_SLAK) != CAN_MSR_SLAK)
  {

    wakeupstatus = CAN_WakeUp_Ok;
  }

  return (uint8_t)wakeupstatus;
}

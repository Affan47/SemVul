CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
  uint8_t transmit_mailbox = 0;

  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_IDTYPE(TxMessage->IDE));
  assert_param(IS_CAN_RTR(TxMessage->RTR));
  assert_param(IS_CAN_DLC(TxMessage->DLC));


  if ((CANx->TSR&CAN_TSR_TME0) == CAN_TSR_TME0)
  {
    transmit_mailbox = 0;
  }
  else if ((CANx->TSR&CAN_TSR_TME1) == CAN_TSR_TME1)
  {
    transmit_mailbox = 1;
  }
  else if ((CANx->TSR&CAN_TSR_TME2) == CAN_TSR_TME2)
  {
    transmit_mailbox = 2;
  }
  else
  {
    transmit_mailbox = CAN_TxStatus_NoMailBox;
  }

  if (transmit_mailbox != CAN_TxStatus_NoMailBox)
  {

    CANx->sTxMailBox[transmit_mailbox].TIR &= TMIDxR_TXRQ;
    if (TxMessage->IDE == CAN_Id_Standard)
    {
      assert_param(IS_CAN_STDID(TxMessage->StdId));
      CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->StdId << 21) | \
                                                  TxMessage->RTR);
    }
    else
    {
      assert_param(IS_CAN_EXTID(TxMessage->ExtId));
      CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->ExtId << 3) | \
                                                  TxMessage->IDE | \
                                                  TxMessage->RTR);
    }


    TxMessage->DLC &= (uint8_t)0x0000000F;
    CANx->sTxMailBox[transmit_mailbox].TDTR &= (uint32_t)0xFFFFFFF0;
    CANx->sTxMailBox[transmit_mailbox].TDTR |= TxMessage->DLC;


    CANx->sTxMailBox[transmit_mailbox].TDLR = (((uint32_t)TxMessage->Data[3] << 24) |
                                             ((uint32_t)TxMessage->Data[2] << 16) |
                                             ((uint32_t)TxMessage->Data[1] << 8) |
                                             ((uint32_t)TxMessage->Data[0]));
    CANx->sTxMailBox[transmit_mailbox].TDHR = (((uint32_t)TxMessage->Data[7] << 24) |
                                             ((uint32_t)TxMessage->Data[6] << 16) |
                                             ((uint32_t)TxMessage->Data[5] << 8) |
                                             ((uint32_t)TxMessage->Data[4]));

    CANx->sTxMailBox[transmit_mailbox].TIR |= TMIDxR_TXRQ;
  }
  return transmit_mailbox;
}

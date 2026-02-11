CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT)
{

  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_IT(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_TME:

      CANx->TSR = CAN_TSR_RQCP0|CAN_TSR_RQCP1|CAN_TSR_RQCP2;
      break;
    case CAN_IT_FF0:

      CANx->RF0R = CAN_RF0R_FULL0;
      break;
    case CAN_IT_FOV0:

      CANx->RF0R = CAN_RF0R_FOVR0;
      break;
    case CAN_IT_FF1:

      CANx->RF1R = CAN_RF1R_FULL1;
      break;
    case CAN_IT_FOV1:

      CANx->RF1R = CAN_RF1R_FOVR1;
      break;
    case CAN_IT_WKU:

      CANx->MSR = CAN_MSR_WKUI;
      break;
    case CAN_IT_SLK:

      CANx->MSR = CAN_MSR_SLAKI;
      break;
    case CAN_IT_EWG:

      CANx->MSR = CAN_MSR_ERRI;

      break;
    case CAN_IT_EPV:

      CANx->MSR = CAN_MSR_ERRI;

      break;
    case CAN_IT_BOF:

      CANx->MSR = CAN_MSR_ERRI;

       break;
    case CAN_IT_LEC:

      CANx->ESR = RESET;

      CANx->MSR = CAN_MSR_ERRI;
      break;
    case CAN_IT_ERR:

      CANx->ESR = RESET;

      CANx->MSR = CAN_MSR_ERRI;

       break;
    default:
       break;
   }
}

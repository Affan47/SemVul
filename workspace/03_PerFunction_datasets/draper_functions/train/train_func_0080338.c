CPAL_I2C_DMA_TX_IRQHandler(CPAL_InitTypeDef* pDevInitStruct)
{

  pDevInitStruct->wCPAL_Timeout = CPAL_I2C_TIMEOUT_DEFAULT;

  CPAL_LOG("\n\r\n\rLOG <CPAL_I2C_DMA_TX_IRQHandler> : I2C Device TX DMA ");


  if((__CPAL_I2C_HAL_GET_DMATX_TCIT(pDevInitStruct->CPAL_Dev)) != 0)
  {
    CPAL_LOG("\n\rLOG : I2C Device TX Complete");


    pDevInitStruct->pCPAL_TransferTx->wNumData = 0;


    CPAL_I2C_DMATXTC_UserCallback(pDevInitStruct);


    if ((pDevInitStruct->wCPAL_Options & CPAL_OPT_DMATX_CIRCULAR) == 0)
    {

      if (pDevInitStruct->CPAL_Mode == CPAL_MODE_MASTER)
      {
 #ifdef CPAL_I2C_MASTER_MODE

        __CPAL_I2C_HAL_DISABLE_DMAREQ(pDevInitStruct->CPAL_Dev);


        __CPAL_I2C_TIMEOUT_SPINLOOP(__CPAL_I2C_HAL_GET_BTF(pDevInitStruct->CPAL_Dev), CPAL_I2C_TIMEOUT_BTF);


        if ((pDevInitStruct->wCPAL_Options & CPAL_OPT_I2C_NOSTOP) == 0)
        {

          __CPAL_I2C_HAL_STOP(pDevInitStruct->CPAL_Dev);


          __CPAL_I2C_TIMEOUT_SPINLOOP(!(__CPAL_I2C_HAL_GET_BUSY(pDevInitStruct->CPAL_Dev)), CPAL_I2C_TIMEOUT_BUSY);
        }


        __CPAL_I2C_HAL_DISABLE_DMATX(pDevInitStruct->CPAL_Dev);


        __CPAL_I2C_HAL_DISABLE_EVTIT(pDevInitStruct->CPAL_Dev);

        CPAL_LOG("\n\rLOG : I2C Device Master TX DMA Disabled");


        pDevInitStruct->CPAL_State = CPAL_STATE_READY;
      }
 #endif
      else
      {
 #ifdef CPAL_I2C_SLAVE_MODE

        __CPAL_I2C_HAL_DISABLE_DMAREQ(pDevInitStruct->CPAL_Dev);
        __CPAL_I2C_HAL_DISABLE_DMATX(pDevInitStruct->CPAL_Dev);


        __CPAL_I2C_HAL_DISABLE_EVTIT(pDevInitStruct->CPAL_Dev);


        __CPAL_I2C_TIMEOUT_SPINLOOP(!(__CPAL_I2C_HAL_GET_BUSY(pDevInitStruct->CPAL_Dev)), CPAL_I2C_TIMEOUT_BUSY);

        CPAL_LOG("\n\rLOG : I2C Device Slave TX DMA Disabled");


        pDevInitStruct->CPAL_State = CPAL_STATE_READY;
 #endif
      }
    }

    CPAL_I2C_TXTC_UserCallback(pDevInitStruct);
  }

  else if ((__CPAL_I2C_HAL_GET_DMATX_HTIT(pDevInitStruct->CPAL_Dev)) != 0)
  {
    CPAL_LOG("\n\rLOG : I2C Device TX DMA Half Transfer ");


    CPAL_I2C_DMATXHT_UserCallback(pDevInitStruct);
  }

  else if ((__CPAL_I2C_HAL_GET_DMATX_TEIT(pDevInitStruct->CPAL_Dev)) != 0)
  {
    CPAL_LOG("\n\rERROR : I2C Device TX DMA Transfer Error ");


    pDevInitStruct->CPAL_State = CPAL_STATE_ERROR;


    pDevInitStruct->pCPAL_TransferTx->wNumData = __CPAL_I2C_HAL_DMATX_GET_CNDT(pDevInitStruct->CPAL_Dev);


    CPAL_I2C_DMATXTE_UserCallback(pDevInitStruct);
  }


    __CPAL_I2C_HAL_CLEAR_DMATX_IT(pDevInitStruct->CPAL_Dev);

  return CPAL_PASS;
}

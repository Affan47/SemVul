DCD_HandleUSBSuspend_ISR(USB_OTG_CORE_HANDLE *pdev)
{
  USB_OTG_GINTSTS_TypeDef  gintsts;
  USB_OTG_PCGCCTL_TypeDef  power;
  USB_OTG_DSTS_TypeDef     dsts;
  __IO uint8_t prev_status = 0;

  prev_status = pdev->dev.device_status;
  USBD_DCD_INT_fops->Suspend (pdev);

  dsts.d32 = USB_OTG_READ_REG32(&pdev->regs.DREGS->DSTS);


  gintsts.d32 = 0;
  gintsts.b.usbsuspend = 1;
  USB_OTG_WRITE_REG32(&pdev->regs.GREGS->GINTSTS, gintsts.d32);

  if((pdev->cfg.low_power) && (dsts.b.suspsts == 1)  &&
    (pdev->dev.connection_status == 1) &&
    (prev_status  == USB_OTG_CONFIGURED))
  {

    power.d32 = 0;
    power.b.stoppclk = 1;
    USB_OTG_MODIFY_REG32(pdev->regs.PCGCCTL, 0, power.d32);

    power.b.gatehclk = 1;
    USB_OTG_MODIFY_REG32(pdev->regs.PCGCCTL, 0, power.d32);


    SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk);
  }
  return 1;
}

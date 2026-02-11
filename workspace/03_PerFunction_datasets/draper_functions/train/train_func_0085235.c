gpioSetInterrupt (uint32_t portNum, uint32_t bitPos, gpioInterruptSense_t sense, gpioInterruptEdge_t edge, gpioInterruptEvent_t event)
{
  if (!_gpioInitialised) gpioInit();


  REG32 *gpiois  = &GPIO_GPIO0IS;
  REG32 *gpioibe = &GPIO_GPIO0IBE;
  REG32 *gpioiev = &GPIO_GPIO0IEV;
  switch (portNum)
  {
    case 0:
      gpiois  = &GPIO_GPIO0IS;
      gpioibe = &GPIO_GPIO0IBE;
      gpioiev = &GPIO_GPIO0IEV;
      break;
    case 1:
      gpiois  = &GPIO_GPIO1IS;
      gpioibe = &GPIO_GPIO1IBE;
      gpioiev = &GPIO_GPIO1IEV;
      break;
    case 2:
      gpiois  = &GPIO_GPIO2IS;
      gpioibe = &GPIO_GPIO2IBE;
      gpioiev = &GPIO_GPIO2IEV;
      break;
    case 3:
      gpiois  = &GPIO_GPIO3IS;
      gpioibe = &GPIO_GPIO3IBE;
      gpioiev = &GPIO_GPIO3IEV;
      break;
  }

  if (sense == gpioInterruptSense_Edge)
  {
    *gpiois &= ~(0x1<<bitPos);

    edge == gpioInterruptEdge_Single ? (*gpioibe &= ~(0x1<<bitPos)) : (*gpioibe |= (0x1<<bitPos));
  }
  else
  {
    *gpiois |= (0x1<<bitPos);
  }

  event == gpioInterruptEvent_ActiveLow ? (*gpioiev &= ~(0x1<<bitPos)) : (*gpioiev |= (0x1<<bitPos));

  return;
}

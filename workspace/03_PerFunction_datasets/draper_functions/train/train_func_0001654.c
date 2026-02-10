ledInit()
{
  int i;

  if(isInit)
    return;

  GPIO_InitTypeDef GPIO_InitStructure;


  RCC_AHB1PeriphClockCmd(LED_GPIO_PERIF, ENABLE);

  for (i = 0; i < LED_NUM; i++)
  {

    GPIO_InitStructure.GPIO_Pin = led_pin[i];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(led_port[i], &GPIO_InitStructure);


    ledSet(i, 0);
  }

  isInit = true;
}

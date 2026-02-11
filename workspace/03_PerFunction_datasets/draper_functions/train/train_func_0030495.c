gtgpsInit(DeckInfo *info)
{
  if(isInit)
    return;

  DEBUG_PRINT("Enabling reading from GlobalTop GPS\n");
  uart1Init(9600);

  xTaskCreate(gtgpsTask, "GTGPS",
              configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  isInit = true;
}

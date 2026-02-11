handleCounter( void* userData, uint64_t time, uint32_t process,
                   uint32_t counter, uint64_t value )
{
  uint64_t i = 0;
  double valueDif = 0.0;
  double timeDif = 0.0;
  double rate = 0.0;
  mapInfoProcessT *currentElement = NULL;
  definitionInfoT *info = (definitionInfoT*)userData;

  while( (i < info->counterCounterDefinition) &&
         (info->counters[i].id != counter))
  {
    i++;
  }
  if( i >= info->counterCounterDefinition )
    return OTF_RETURN_ABORT;


  if( ((info->counters[i].properties) & OTF_COUNTER_TYPE_BITS)
      == OTF_COUNTER_TYPE_ACC )
  {
    if( (info->counters)[i].processMap == NULL )
      (info->counters)[i].processMap = hash_new();


    currentElement = hash_search( info->counters[i].processMap, process );

    if( !currentElement )
    {
      currentElement = hash_add( info->counters[i].processMap, process );
    }
    else
    {
      valueDif = value - currentElement->lastValue;
      timeDif = time - currentElement->lastTime;

      if( timeDif > 0 )
      {
        rate = (valueDif / timeDif) * (double)(info->timerResolution);
      }
      if( rate > currentElement->highestRate )
        currentElement->highestRate = rate;
    }

    currentElement->lastValue = value;
    currentElement->lastTime = time;
  }

  return OTF_RETURN_OK;
}

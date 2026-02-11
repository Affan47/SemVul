uxTaskGetTaskNumber( TaskHandle_t xTask )
	{
	UBaseType_t uxReturn;
	TCB_t *pxTCB;

		if( xTask != NULL )
		{
			pxTCB = ( TCB_t * ) xTask;
			uxReturn = pxTCB->uxTaskNumber;
		}
		else
		{
			uxReturn = 0U;
		}

		return uxReturn;
	}

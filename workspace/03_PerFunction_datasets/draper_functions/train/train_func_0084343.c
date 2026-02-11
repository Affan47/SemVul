vQueueUnregisterQueue( QueueHandle_t xQueue )
	{
	UBaseType_t ux;


		for( ux = ( UBaseType_t ) 0U; ux < ( UBaseType_t ) configQUEUE_REGISTRY_SIZE; ux++ )
		{
			if( xQueueRegistry[ ux ].xHandle == xQueue )
			{

				xQueueRegistry[ ux ].pcQueueName = NULL;
				break;
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}

	}

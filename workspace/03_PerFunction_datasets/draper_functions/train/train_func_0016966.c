vPortValidateInterruptPriority( void )
	{
	uint32_t ulCurrentInterrupt;
	uint8_t ucCurrentPriority;


		__asm volatile( "mrs %0, ipsr" : "=r"( ulCurrentInterrupt ) );


		if( ulCurrentInterrupt >= portFIRST_USER_INTERRUPT_NUMBER )
		{

			ucCurrentPriority = pcInterruptPriorityRegisters[ ulCurrentInterrupt ];


			configASSERT( ucCurrentPriority >= ucMaxSysCallPriority );
		}


		configASSERT( ( portAIRCR_REG & portPRIORITY_GROUP_MASK ) <= ulMaxPRIGROUPValue );
	}

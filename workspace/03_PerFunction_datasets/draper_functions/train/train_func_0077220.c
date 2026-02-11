IRQ(int int_level, int count)
{
	int i = 1 << int_level;

	if (int_level == 5) C.resetCounter();


        if( (irq_enable & i) == 0) {

                return;
		}

	if (int_level == 5) timerCounter += count;


        if( (irq_pending & i) ) {
				D(bug("same interrupt %d already pending", int_level));
                return;
		}


#if 0
        if(int_level) {
          panicbug( "mfp ask interrupt %d\n", int_level) ;
        }
#endif
        irq_pending |= i ;

        if( ! (irq_mask & i) ) {

               D(bug("irq_pending set but no irq"));
          return ;
        }

        if(irq_inservice > i) {


				panicbug("irq_inservice has higher priority");
                return ;
        }

        TriggerMFP(true);


}

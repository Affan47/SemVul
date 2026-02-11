AbortOutOfAnyTransaction(void)
{
	TransactionState s = CurrentTransactionState;


	do
	{
		switch (s->blockState)
		{
			case TBLOCK_DEFAULT:
				if (s->state == TRANS_DEFAULT)
				{

				}
				else
				{


					if (s->state == TRANS_START)
						s->state = TRANS_INPROGRESS;
					AbortTransaction();
					CleanupTransaction();
				}
				break;
			case TBLOCK_STARTED:
			case TBLOCK_BEGIN:
			case TBLOCK_INPROGRESS:
			case TBLOCK_PARALLEL_INPROGRESS:
			case TBLOCK_END:
			case TBLOCK_ABORT_PENDING:
			case TBLOCK_PREPARE:

				AbortTransaction();
				CleanupTransaction();
				s->blockState = TBLOCK_DEFAULT;
				break;
			case TBLOCK_ABORT:
			case TBLOCK_ABORT_END:

				CleanupTransaction();
				s->blockState = TBLOCK_DEFAULT;
				break;


			case TBLOCK_SUBBEGIN:
			case TBLOCK_SUBINPROGRESS:
			case TBLOCK_SUBRELEASE:
			case TBLOCK_SUBCOMMIT:
			case TBLOCK_SUBABORT_PENDING:
			case TBLOCK_SUBRESTART:
				AbortSubTransaction();
				CleanupSubTransaction();
				s = CurrentTransactionState;
				break;

			case TBLOCK_SUBABORT:
			case TBLOCK_SUBABORT_END:
			case TBLOCK_SUBABORT_RESTART:

				CleanupSubTransaction();
				s = CurrentTransactionState;
				break;
		}
	} while (s->blockState != TBLOCK_DEFAULT);


	Assert(s->parent == NULL);
}

ompfbe_mpi_task_is_write_barrier(Statement *stm)
{
    Statement *sp;
    Quadruple *qp;

    for( sp = stm->next; sp != NULL && sp->ope != OPE_SYNCA; sp = sp->next){
	for( qp = sp->qr_head; qp != NULL; qp = qp->next){
	    if( qp->ope == OPE_RECEIVE){
		return FALSE;
	    }
	}
    }

    for( sp = stm->prev; sp != NULL && sp->ope != OPE_SYNCA; sp = sp->prev){
	for( qp = sp->qr_head; qp != NULL; qp = qp->next){
	    if( qp->ope == OPE_SEND){
		return FALSE;
	    }
	}
    }

    return TRUE;
}

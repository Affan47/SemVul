Ns_SemaDestroy(Ns_Sema *semaPtr)
{
    if (*semaPtr != NULL) {
    	Sema *sPtr = (Sema *) *semaPtr;

    	Ns_MutexDestroy(&sPtr->lock);
    	Ns_CondDestroy(&sPtr->cond);
    	ns_free(sPtr);
    	*semaPtr = NULL;
    }
}

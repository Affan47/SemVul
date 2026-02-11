zFreeConseq(zConseq *conseq) {
	if(conseq->seq != NULL){
		zFreeSequence(conseq->seq);
		zFree(conseq->seq);
		conseq->seq = NULL;
	}
	if(conseq->def != NULL){
		zFree(conseq->def);
		conseq->def = NULL;
	}
}

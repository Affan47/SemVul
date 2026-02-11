queue_is_full(queue* q){
    if((q->front == q->rear) && (q->array[q->front].payload != NULL)){
	return 1;
    }
    else{
	return 0;
    }
}

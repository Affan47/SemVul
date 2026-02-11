eoquantum(){
	age_process();
	struct queue_t *temp = get_process(RUNNING);

	if(temp->head != null){
		if(temp->head->priority > 1){
			temp->head->priority--;
		}
	}

    return move(RUNNING, READY);
}

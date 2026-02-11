create(int psw, int page_table, int *reg){
    int error;

    if(process_counter >= MAX_PROCESSES){
        return -2;
    }

	int pid = pid_counter;
	pid_counter++;

    if ((find_process(get_process(WAITING), pid) != null) ||
        ((find_process(get_process(READY), pid)) != null) ||
        ((find_process(get_process(TERMINATED), pid)) != null) ||
        ((find_process(get_process(RUNNING), pid)) != null)) {
        return -3;
    }


    error = enqueue(get_process(NEW), pid, psw, page_table, reg, 10, 0);


    if (error == -1){
        return -666;
    }
    process_counter++;

    return move(NEW, READY);
}

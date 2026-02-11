enum_to_string(enum QUEUES queue){
    switch (queue) {
    case NEW:
        return "New Queue";
    case WAITING:
        return "Waiting Queue";
    case READY0:
        if(scheduler == GROUP){
            return "Group 0 Ready Queue";
        }
        else{
            return "Ready Queue";
        }
    case READY1:
        return "Group 1 Ready Queue";
    case READY2:
        return "Group 2 Ready Queue";
    case READY3:
        return "Group 3 Ready Queue";
    case TERMINATED:
        return "Terminated Queue";
    case RUNNING:
        return "Running Queue";
    default:
        return "No Such Queue";
    }
}

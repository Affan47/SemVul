K_request_process_status(MsgEnv *msg_env)
{
	PCB *temp;

	char pid[15];
	char status[25];
	char priority[25];
	strcpy(priority, "priority: ");
	strcpy(pid,"PID: ");
	strcpy(status, "status: ");

	int to_return;
	int i;
	char buffer[100];

	for(i=1; i<=(USR_PROC_NUMB); i++){
		temp = PCB_finder(i);
		strcat (pid, itoa(temp->pid, buffer));
		strcat (pid,",");
		strcat (status, itoa(temp->status, buffer));
		strcat (status,",");
		strcat (priority, itoa(temp->priority, buffer));
		strcat (priority,",");
	}
	char proc_status[TEXT_AREA_SIZE];
	strcpy (proc_status, pid);
	strcat (proc_status, "\n");
	strcat (proc_status, status);
	strcat (proc_status, "\n");
	strcat (proc_status, priority);
	strcat (proc_status, "\n");
	strcpy(msg_env->text_area,proc_status);

	to_return = K_send_message(msg_env->dest_id, msg_env);
	return to_return;
}

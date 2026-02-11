K_send_console_chars(MsgEnv *msg_env)
{
	msg_env->dest_id = crt_i_proc->pid;
	msg_env->type = DISPLAY_ACKNOWLEDGEMENT;

	int return_value = K_send_message(crt_i_proc->pid, msg_env);

	PCB *temp;
	if(printed == 1){
		printed = 0;
		temp = current_process;
		current_process = crt_i_proc;
		CRT_I_Proc();
		current_process = temp;
	}
	return return_value;
}

message_loop(int erlin_fd)
{
    char cmdLen, cmd;
    int res;

    while (1){


	if ((res = read(erlin_fd, &cmdLen, 1)) < 0) {
	    print_error("Error reading from Erlang");
	    return;
	}

	if (res == 1) {
	    if (cmdLen == 1){
		switch (read(erlin_fd, &cmd, 1)){
		case 1:
		    switch (cmd){
		    case SHOW_MEM:
			simple_show_mem();
			break;
		    case SHOW_SYSTEM_MEM:
			extended_show_mem();
			break;
		    default:
			break;
		    }
		  break;

		case 0:
		  print_error("Erlang has closed");
		  return;

		default:
		  print_error("Error reading from Erlang");
		  return;
		}
	    } else {
		print_error("Invalid command length (%d) received", cmdLen);
		return;
	    }
	} else {
	    print_error("Erlang has closed");
	    return;
	}
    }
}

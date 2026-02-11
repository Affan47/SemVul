command_line(int argc,char **argv) {
	std::string command = "";
	for(int i=0;i<argc;i++){
	    if(i>0) command += " ";
	    command += argv[i];
	}
	return command;
    }

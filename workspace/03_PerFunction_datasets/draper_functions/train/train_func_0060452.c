open_out_files(struct prog_info *pi, char *filename)
{
	int length;
	char *buff;
	int ok = True;

	length = strlen(filename);
	buff = malloc(length + 9);
	if(buff == NULL) {
	  print_msg(pi, MSGTYPE_OUT_OF_MEM, NULL);
    return(False);
  }
  strcpy(buff, filename);
  if(length < 4) {
    printf("Error: wrong input file name\n");
  }
  if(!nocase_strcmp(&buff[length - 4], ".asm")) {
	  length -= 4;
	  buff[length] = '\0';
	}


  strcpy(&buff[length], ".hex");
	if(!(pi->hfi = open_hex_file(buff))) {
    print_msg(pi, MSGTYPE_ERROR, "Could not create output hex file!");
    ok = False;
  }
  strcpy(&buff[length], ".obj");
  if(!(pi->obj_file = open_obj_file(pi, buff))) {
    print_msg(pi, MSGTYPE_ERROR, "Could not create object file!");
    ok = False;
  }


  strcpy(&buff[length], ".eep.hex");
  if(!(pi->eep_hfi = open_hex_file(buff))) {
		print_msg(pi, MSGTYPE_ERROR, "Could not create eeprom hex file!");
    ok = False;
  }

  strcpy(&buff[length], ".cof");
	pi->coff_file = open_coff_file(pi, buff);

	if (pi->list_on) {
    strcpy(buff, GET_ARG(pi->args, ARG_LISTFILE));
    pi->list_file = fopen(buff, "w");
    if(pi->list_file == NULL) {
			print_msg(pi, MSGTYPE_ERROR, "Could not create list file!");
      ok = False;
    }

    fprintf(pi->list_file, "\nAVRA   Ver. %i.%i.%i %s %s\n\n",VER_MAJOR, VER_MINOR, VER_RELEASE, filename, ctime(&pi->time));
  }
  else {
    pi->list_file = NULL;
  }
  free(buff);

	if(ok)
	  return(True);
  else
	  close_out_files(pi);
  return(False);
}

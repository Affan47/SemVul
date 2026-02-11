Register_ChkType(char* ChkLabel,
		     int   direction,
		     int   ChkFrequency,
		     int   *ChkType)
{
  int current;
  int iparam;
  int new_size;
  IOdef_entry* dum_ptr;


  if(!ReG_SteeringEnabled) {
    *ChkType = REG_IODEF_HANDLE_NOTSET;
    return REG_SUCCESS;
  }


  if(!ReG_SteeringInit) return REG_FAILURE;


  current = ChkTypes_table.num_registered;

  if(String_contains_xml_chars(ChkLabel) == REG_TRUE) {
    fprintf(stderr, "STEER: ERROR: Register_ChkType: Chk label contains "
	    "reserved xml characters (<,>,&): %s\n", ChkLabel);
    return REG_FAILURE;
  }

  strcpy(ChkTypes_table.io_def[current].label, ChkLabel);


  ChkTypes_table.io_def[current].direction = direction;


  if(direction != REG_IO_IN) {


    ChkTypes_table.io_def[current].frequency = ChkFrequency;

    Register_param("Chk_Frequency",
		   REG_TRUE,
		   (void *)&(ChkTypes_table.io_def[current].frequency),
		   REG_INT,
		   "0", " ");


    ChkTypes_table.io_def[current].freq_param_handle =
	                               Params_table.next_handle - 1;


    iparam = Param_index_from_handle(&Params_table,
			  ChkTypes_table.io_def[current].freq_param_handle);
    if(iparam != -1) {
      Params_table.param[iparam].is_internal = REG_TRUE;
    }
    else {
#ifdef REG_DEBUG
      fprintf(stderr, "STEER: Register_ChkType: failed to get handle for param\n");
#endif
      *ChkType = REG_IODEF_HANDLE_NOTSET;
      return REG_FAILURE;
    }
  }
  else {


    ChkTypes_table.io_def[current].freq_param_handle = REG_PARAM_HANDLE_NOTSET;
    ChkTypes_table.io_def[current].frequency = 0;
  }


  ChkTypes_table.io_def[current].buffer = NULL;
  ChkTypes_table.io_def[current].buffer_bytes = 0;
  ChkTypes_table.io_def[current].buffer_max_bytes = 0;


  ChkTypes_table.io_def[current].handle = Next_IO_Chk_handle++;
  *ChkType = ChkTypes_table.io_def[current].handle;


  current++;
  if(current == ChkTypes_table.max_entries) {
    new_size = ChkTypes_table.max_entries + REG_INITIAL_NUM_IOTYPES;

    dum_ptr = (IOdef_entry*)realloc((void *)(ChkTypes_table.io_def),
		                    new_size*sizeof(IOdef_entry));

    if(dum_ptr == NULL) {
      fprintf(stderr, "STEER: Register_ChkType: failed to allocate memory\n");
      return REG_FAILURE;
    }
    else {

      ChkTypes_table.io_def = dum_ptr;
    }

    ChkTypes_table.max_entries += REG_INITIAL_NUM_IOTYPES;
  }

  ChkTypes_table.num_registered = current;


  ReG_ChkTypesChanged = REG_TRUE;

  return REG_SUCCESS;
}

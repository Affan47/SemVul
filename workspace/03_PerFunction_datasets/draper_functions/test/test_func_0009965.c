irplib_error_validate_state (const char *func, const char *file,
			     unsigned int line)
{
  if (!is_initialized) {
    cpl_msg_error (__func__, "Error handling system was not initialized "
		   "when called from %s:%s:%d!", file, func, line);
    return;
  }
  if (cpl_error_get_code () == CPL_ERROR_NONE) {
    if (queue.is_empty) {

    }
    else {


      xsh_irplib_error_reset ();
    }
  }
  else {


    irplib_error er;


    if (!queue.is_empty) {
      er = queue.errors[queue.last];
    }


    if (queue.is_empty ||
	!(strcmp (er.filename, cpl_error_get_file ()) == 0 &&
	  strcmp (er.function, cpl_error_get_function ()) == 0 &&
	  strcmp (er.cplmessage, cpl_error_get_message ()) == 0 &&

	  er.errorcode == cpl_error_get_code () &&
	  er.linenumber == cpl_error_get_line ()
	)
      ) {


      char file_cpl[MAX_STRING_LENGTH];
      char func_cpl[MAX_STRING_LENGTH];
      cpl_error_code ec_cpl;
      unsigned int line_cpl;

      char message_local[MAX_STRING_LENGTH];


      strncpy (file_cpl, cpl_error_get_file (), MAX_STRING_LENGTH - 1);
      file_cpl[MAX_STRING_LENGTH - 1] = '\0';

      strncpy (func_cpl, cpl_error_get_function (), MAX_STRING_LENGTH - 1);
      func_cpl[MAX_STRING_LENGTH - 1] = '\0';

      ec_cpl = cpl_error_get_code ();
      line_cpl = cpl_error_get_line ();


      if (queue.is_empty) {
	cpl_error_reset ();
      }
      else {
	cpl_error_set_message_macro (er.function,
			     er.errorcode, er.filename, er.linenumber," ");
      }


      strncpy (message_local, error_msg, MAX_STRING_LENGTH - 1);
      message_local[MAX_STRING_LENGTH - 1] = '\0';


      xsh_irplib_error_set_msg (" ");
      xsh_irplib_error_push_macro (func_cpl, ec_cpl, file_cpl, line_cpl);
      xsh_irplib_error_set_msg ("%s", message_local);

    }

  }

  return;
}

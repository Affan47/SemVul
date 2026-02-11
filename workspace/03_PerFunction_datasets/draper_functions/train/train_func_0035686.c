print_vpi_call_errors()
{
      for (unsigned idx = 0; idx < vpi_call_error_num; idx += 1) {
	    switch (vpi_call_error_lst[idx].type) {
		case VPI_CALL_NO_DEF:
		  fprintf(stderr, "%s:%d: Error: System task/function %s() is "
		                  "not defined by any module.\n",
		                  file_names[vpi_call_error_lst[idx].file_idx],
		                  (int)vpi_call_error_lst[idx].lineno,
		                  vpi_call_error_lst[idx].name);
		  break;
		case VPI_CALL_TASK_AS_FUNC:
		  fprintf(stderr, "%s:%d: Error: %s() is a system task, it "
			          "cannot be called as a function.\n",
		                  file_names[vpi_call_error_lst[idx].file_idx],
		                  (int)vpi_call_error_lst[idx].lineno,
		                  vpi_call_error_lst[idx].name);
		  break;
		case VPI_CALL_FUNC_AS_TASK:
		  fprintf(stderr, "%s:%d: Error: %s() is a system function, it "
			          "cannot be called as a task.\n",
		                  file_names[vpi_call_error_lst[idx].file_idx],
		                  (int)vpi_call_error_lst[idx].lineno,
		                  vpi_call_error_lst[idx].name);
		  break;
	    }
	    free(vpi_call_error_lst[idx].name);
      }
      free(vpi_call_error_lst);
      fflush(stderr);
}

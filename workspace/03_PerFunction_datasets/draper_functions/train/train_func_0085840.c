push_include_file(char *fname, srcLine *newbuf, LINENO_t include_line_num)
{
	 if (incdepth == MAX_INCLUDE_DEPTH) {
	   oops_message(OOPS_NONFATAL,line_num,NO_COL_NUM,
			"include files nested too deep");
	   return FALSE;
	 }

#ifdef DEBUG_INCLUDE
if(debug_include){
(void)fprintf(list_fd,"\npush_include_file: curr_srcLine=%s\n next_srcLine=%s",
	      curr_srcLine?curr_srcLine->line:NULL,
	      next_srcLine?next_srcLine->line:NULL);
}
#endif

	 if(incdepth == 0)
	   top_file_line_num = include_line_num;

	 include_stack[incdepth].input_buf = srcBuffer;
	 include_stack[incdepth].curr_input_line = curr_srcLine;
	 include_stack[incdepth].next_input_line = next_srcLine;
	 srcBuffer = newbuf;

	 include_stack[incdepth].fname = current_filename;
	 current_filename = fname;

	 include_stack[incdepth].curr_char = curr_char;
	 include_stack[incdepth].next_char = next_char;
	 include_stack[incdepth].next_index = next_index;
	 include_stack[incdepth].col_num = col_num;
	 include_stack[incdepth].next_col_num = next_col_num;
	 include_stack[incdepth].line_num = line_num;
	 include_stack[incdepth].next_line_num = next_line_num;
	 include_stack[incdepth].do_list = do_list;
	 include_stack[incdepth].inctable_index = inctable_index;

	 incdepth++;

	 init_stream();

	 return TRUE;
}

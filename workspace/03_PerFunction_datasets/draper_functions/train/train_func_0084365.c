advance(VOID)
{
    prev_char = curr_char;

    if(next_char == EOF) {
	if(curr_char == EOS || curr_char == EOF) {


		  if(sticky_EOF) {
		    sticky_EOF = FALSE;
		    return;
		  }


		  if( ! pop_include_file() ) {
		    curr_char = EOF;
		  }
		  return;
	}
	else {
		  curr_char = EOS;
		  return;
	}
    }

    if(curr_char == EOS)
	initial_flag = TRUE;

    curr_char = next_char;
    col_num = next_col_num;
    line_num = next_line_num;
    curr_srcLine = next_srcLine;


#ifdef ALLOW_UNIX_CPP
    if(next_index == 0 && next_char == '#')
	cpp_handled = take_cpp_line(next_srcLine);
#endif

    next_col_num = NXTCOL(next_char,next_col_num);

    next_index++;


    while( next_index > next_srcLine->end_index ) {


	if( next_char == EOS || next_char == EOL ) {


	  if( curr_srcLine != (srcLine *)NULL )
	      prev_stmt_line_num = curr_srcLine->line_num;


	  do {


	    if( next_srcLine->contin )
	      contin_count++;
	    else
	      contin_count = 0;

	    finish_off_srcLine(next_srcLine);


	    next_srcLine = next_srcLine->next;

	    if( next_srcLine == (srcLine *)NULL ) {
		next_char = EOF;
		return;
	    }


	    next_line_num = next_srcLine->line_num;


	    ++tot_line_count;

	    if( ! next_srcLine->comment ) {

		++tot_stmt_line_count;
		++noncomment_line_count;
	    }
	  } while( next_srcLine->comment );

	  next_index = next_srcLine->start_index;
	  next_col_num = next_srcLine->start_col;


	  if( next_srcLine->contin &&
	     next_srcLine->line[next_index] == '\0' ) {
	    next_char = EOL;
	    return;
	  }

	}

	else {


	    srcLine *p = next_srcLine->next;
	    while( p != NULL && p->comment ) {
		p = p->next;
	    }
	    if( p != NULL && p->contin ) {
		int i = p->start_index;


		next_char = EOL;
		if( free_form ) {
		    if( i <= p->end_index &&
			(i == 0 || p->line[i-1] != '&') ) {
			return;
		    }
		}
		else {
		    if( col_num < max_stmt_col ) {
			return;
		    }
		}


	    }
	    else {

		next_char = EOS;
		return;
	    }
	}

    }


    next_char = next_srcLine->line[next_index];


    if(next_up(';')) {
	next_char = EOS;
	if(f77_semicolon) {
	    nonstandard(next_line_num,next_col_num,0,0);
	    msg_tail("semicolon statement separator");
	}
    }


}

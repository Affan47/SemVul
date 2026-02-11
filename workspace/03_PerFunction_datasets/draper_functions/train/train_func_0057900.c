do_format(FILE *infile, FILE *outfile)
#endif
{
    int token_type, was_c_token;
    expptr retval = ENULL;

    token_type = get_p1_token (infile);
    was_c_token = 1;
    switch (token_type) {
	case P1_COMMENT:
	    do_p1_comment (infile, outfile);
	    was_c_token = 0;
	    break;
	case P1_SET_LINE:
	    do_p1_set_line (infile);
	    was_c_token = 0;
	    break;
	case P1_FILENAME:
	    p1gets(infile, filename, P1_FILENAME_MAX);
	    was_c_token = 0;
	    break;
	case P1_NAME_POINTER:
	    retval = do_p1_name_pointer (infile);
	    break;
	case P1_CONST:
	    retval = do_p1_const (infile);
	    break;
	case P1_EXPR:
	    retval = do_p1_expr (infile, outfile);
	    break;
	case P1_IDENT:
	    retval = do_p1_ident(infile);
	    break;
	case P1_CHARP:
		retval = do_p1_charp(infile);
		break;
	case P1_EXTERN:
	    retval = do_p1_extern (infile);
	    break;
	case P1_HEAD:
	    gflag1 = sharp_line = 0;
	    retval = do_p1_head (infile, outfile);
	    gflag1 = sharp_line = gflag;
	    break;
	case P1_LIST:
	    retval = do_p1_list (infile, outfile);
	    break;
	case P1_LITERAL:
	    retval = do_p1_literal (infile);
	    break;
	case P1_LABEL:
	    do_p1_label (infile, outfile);

	    was_c_token = 0;
	    break;
	case P1_ASGOTO:
	    do_p1_asgoto (infile, outfile);
	    break;
	case P1_GOTO:
	    do_p1_goto (infile, outfile);
	    break;
	case P1_IF:
	    do_p1_if (infile, outfile);
	    break;
	case P1_ELSE:
	    SEM_CHECK(outfile);
	    do_p1_else (outfile);
	    break;
	case P1_ELIF:
	    SEM_CHECK(outfile);
	    do_p1_elif (infile, outfile);
	    break;
	case P1_ENDIF:
	    SEM_CHECK(outfile);
	    do_p1_endif (outfile);
	    break;
	case P1_ENDELSE:
	    SEM_CHECK(outfile);
	    do_p1_endelse (outfile);
	    break;
	case P1_ADDR:
	    retval = do_p1_addr (infile, outfile);
	    break;
	case P1_SUBR_RET:
	    do_p1_subr_ret (infile, outfile);
	    break;
	case P1_COMP_GOTO:
	    do_p1_comp_goto (infile, outfile);
	    break;
	case P1_FOR:
	    do_p1_for (infile, outfile);
	    break;
	case P1_ENDFOR:
	    SEM_CHECK(outfile);
	    do_p1_end_for (outfile);
	    break;
	case P1_WHILE1START:
		do_p1_1while(outfile);
		break;
	case P1_WHILE2START:
		do_p1_2while(infile, outfile);
		break;
	case P1_PROCODE:
		procode(outfile);
		break;
	case P1_ELSEIFSTART:
		SEM_CHECK(outfile);
		do_p1_elseifstart(outfile);
		break;
	case P1_FORTRAN:
		do_p1_fortran(infile, outfile);

	case P1_EOF:
	    was_c_token = 0;
	    break;
	case P1_UNKNOWN:
	    Fatal("do_format:  Unknown token type in intermediate file");
	    break;
	default:
	    Fatal("do_format:  Bad token type in intermediate file");
	    break;
   }

    if (was_c_token)
	last_was_label = 0;
    return retval;
}

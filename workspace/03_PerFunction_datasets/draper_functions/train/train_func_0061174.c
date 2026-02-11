sema_encode_msg(sema_msg* pmsg, char* str) {
    struct sm_submit_invoke *submit_sm = NULL;
    Octstr *IA5msg = NULL;
    int tSize = 0;
    unsigned char oc1byte[10];
    IA5msg = octstr_create("");
    switch(pmsg->type)
    {
    case 'S':
	submit_sm = (struct sm_submit_invoke *) pmsg->msgbody;
	write_variable_value(submit_sm->msisdnlen, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	line_append_hex_IA5(IA5msg,
			    (unsigned char *)octstr_get_cstr(submit_sm->msisdn),
			    octstr_len(submit_sm->msisdn));
	write_variable_value(submit_sm->smereftype, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	line_append_hex_IA5(IA5msg, submit_sm->smerefnum,4);
	write_variable_value(submit_sm->priority, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	write_variable_value(submit_sm->origaddlen, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	line_append_hex_IA5(IA5msg,
			    (unsigned char *)octstr_get_cstr(submit_sm->origadd),
			    octstr_len(submit_sm->origadd));
	write_variable_value(submit_sm->validperiodtype, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	write_variable_value(submit_sm->validperiodrela, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	write_variable_value(submit_sm->DCS, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	write_variable_value(submit_sm->statusreportrequest, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte,1);
	write_variable_value(submit_sm->protocal, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte, 1);
	write_variable_value(submit_sm->replypath, oc1byte);
	line_append_hex_IA5(IA5msg, oc1byte, 1);


      	tSize = internal_char_hex_to_IA5(submit_sm->textsizeseptet,oc1byte);
	octstr_insert_data(IA5msg, octstr_len(IA5msg), (char *)oc1byte, tSize);


	tSize = internal_char_hex_to_IA5(submit_sm->textsizeoctect,oc1byte);
 	octstr_insert_data(IA5msg, octstr_len(IA5msg),(char *) oc1byte, tSize);

	line_append_hex_IA5(IA5msg,
			    (unsigned char *)octstr_get_cstr(submit_sm->shortmsg),
			    submit_sm->textsizeoctect);
	memcpy(str,octstr_get_cstr(IA5msg),octstr_len(IA5msg));
	octstr_destroy(IA5msg);
	return 1;
    }
    return 0;
}

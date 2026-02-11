prepend_catenation_udh(Msg *sms, int part_no, int num_messages,
    	    	    	    	   int msg_sequence)
{
    if (sms->sms.udhdata == NULL)
        sms->sms.udhdata = octstr_create("");
    if (octstr_len(sms->sms.udhdata) == 0)
	octstr_append_char(sms->sms.udhdata, CATENATE_UDH_LEN);
    octstr_format_append(sms->sms.udhdata, "%c\3%c%c%c",
    	    	    	 0, msg_sequence, num_messages, part_no);


     if (part_no < num_messages)
     	sms->sms.msg_left = num_messages - part_no;
     else
     	sms->sms.msg_left = 0;


    octstr_set_char(sms->sms.udhdata, 0, octstr_len(sms->sms.udhdata) - 1 );
}

html_address(HANDLER_S *hd, int ch, int cmd)
{
    int	 j;
#define	HTML_ADD_INDENT	2

    if(cmd == GF_DATA){
	html_handoff(hd, ch);
    }
    else if(cmd == GF_RESET){
	if(PASS_HTML(hd->html_data)){
	    html_output_raw_tag(hd->html_data, "address");
	}
	else{


	    html_indent(hd->html_data, HTML_ADD_INDENT, HTML_ID_INC);
	    j = HD(hd->html_data)->wrapstate;
	    HD(hd->html_data)->wrapstate = 0;
	    html_blank(hd->html_data, 1);
	    HD(hd->html_data)->wrapstate = j;
	}
    }
    else if(cmd == GF_EOD){
	if(PASS_HTML(hd->html_data)){
	    html_output_string(hd->html_data, "</address>");
	}
	else{
	    html_blank(hd->html_data, 1);

	    j = HD(hd->html_data)->wrapstate;
	    HD(hd->html_data)->wrapstate = 0;
	    html_indent(hd->html_data, -(HTML_ADD_INDENT), HTML_ID_INC);
	    HD(hd->html_data)->wrapstate = j;
	}
    }

    return(1);
}

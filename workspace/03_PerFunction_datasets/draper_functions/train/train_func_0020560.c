html_map(HANDLER_S *hd, int ch, int cmd)
{
    if(PASS_HTML(hd->html_data) && PASS_IMAGES(hd->html_data)){
	if(cmd == GF_DATA){
	    html_handoff(hd, ch);
	}
	else if(cmd == GF_RESET){
	    html_output_raw_tag(hd->html_data, "map");
	}
	else if(cmd == GF_EOD){
	    html_output_string(hd->html_data, "</map>");
	}

	return(1);
    }

    return(0);
}

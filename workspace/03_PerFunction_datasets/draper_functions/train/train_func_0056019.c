html_h5(HANDLER_S *hd, int ch, int cmd)
{
    if(cmd == GF_DATA){
	html_handoff(hd, ch);
    }
    else if(cmd == GF_RESET){
	if(PASS_HTML(hd->html_data)){
	    html_output_raw_tag(hd->html_data, "h5");
	}
	else{


	    hd->x = CENTER_BIT(hd->html_data);
	    CENTER_BIT(hd->html_data) = 0;
	    hd->y = html_indent(hd->html_data, 6, HTML_ID_SET);
	    hd->z = HD(hd->html_data)->wrapcol;
	    HD(hd->html_data)->wrapcol = WRAP_COLS(hd->html_data) - 8;
	    html_blank(hd->html_data, 1);
	}
    }
    else if(cmd == GF_EOD){
	if(PASS_HTML(hd->html_data)){
	    html_output_string(hd->html_data, "</h5>");
	}
	else{


	    html_indent(hd->html_data, (int) hd->y, HTML_ID_SET);
	    html_blank(hd->html_data, 1);
	    CENTER_BIT(hd->html_data)  = hd->x;
	    HD(hd->html_data)->wrapcol = hd->z;
	}
    }

    return(1);
}

mhelp(void)
{
    char *p, buf[MAX_LINELEN+1];
    main_phtml_put(""); buf[0]=0;
    if(cmd_type!=cmd_help) {
	phtml_put_base("closemhelp.phtml",0);
    }
    else {
	phtml_put_base("mhelpheader.phtml",0);
	p=getvar("special_parm");
	if(p!=NULL && strcmp(p,"about")==0)
	  phtml_put("about.phtml",0);
	else phtml_put("help.phtml",0); phtml_put_base("mhelptail.phtml",0);
	exec_tail(buf);
    }
}

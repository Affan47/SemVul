get_option_line(int line_num){
    OptionList *opl;
    char *op_str;
    int i;

    opl = op_list;
    for(i=1;i<line_num;i++){
	if(opl == NULL){
	    return NULL;
	}
	opl = opl->next;
    }

    if(opl == NULL){
	return NULL;
    }
    else{
	op_str = (char *)malloc(sizeof(char)*(strlen(opl->option_str)+1));
	if(op_str == NULL){
	    fatal("not enough memory\n");
	}
	strcpy(op_str,opl->option_str);
    }

    return op_str;
}

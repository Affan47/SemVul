line_is_blank(char* line){
    int i=0;

    for(i=0; *(line+i)!=0; i++){
	char c = *(line+i);

	if(c != ' ' && c != '\n' && c != '\t'){
	    return 0;
	}
    }

    return 1;
}

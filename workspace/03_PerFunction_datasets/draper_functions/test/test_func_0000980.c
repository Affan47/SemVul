parse_pattern(char *label, char *str, int hex_to_backslashed)
{
    char       copy[50];
    char       copynot[50];
    char      *q, *labeled_str;
    PATTERN_S *head = NULL;

    if(!label || !str)
      return(NULL);

    q = copy;
    sstrncpy(&q, "/", sizeof(copy));
    sstrncpy(&q, label, sizeof(copy) - (q-copy));
    sstrncpy(&q, "=", sizeof(copy) - (q-copy));
    copy[sizeof(copy)-1] = '\0';
    q = copynot;
    sstrncpy(&q, "/!", sizeof(copynot));
    sstrncpy(&q, label, sizeof(copynot) - (q-copynot));
    sstrncpy(&q, "=", sizeof(copynot) - (q-copynot));
    copynot[sizeof(copynot)-1] = '\0';

    if(hex_to_backslashed){
	if((q = srchstr(str, copy)) != NULL){
	    head = config_to_pattern(q+strlen(copy));
	}
	else if((q = srchstr(str, copynot)) != NULL){
	    head = config_to_pattern(q+strlen(copynot));
	    head->not = 1;
	}
    }
    else{
	if((q = srchstr(str, copy)) != NULL){
	    if((labeled_str =
			remove_backslash_escapes(q+strlen(copy))) != NULL){
		head = string_to_pattern(labeled_str);
		fs_give((void **)&labeled_str);
	    }
	}
	else if((q = srchstr(str, copynot)) != NULL){
	    if((labeled_str =
			remove_backslash_escapes(q+strlen(copynot))) != NULL){
		head = string_to_pattern(labeled_str);
		head->not = 1;
		fs_give((void **)&labeled_str);
	    }
	}
    }

    return(head);
}

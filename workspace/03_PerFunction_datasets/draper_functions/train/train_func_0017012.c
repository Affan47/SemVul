config_to_hdrtok(char *str)
{
    HEADER_TOK_S *hdrtok = NULL;
    char *p, *q;
    int j;

    if(str && *str){
	if((q = remove_pat_escapes(str)) != NULL){
	    char *hn = NULL, *fn = NULL, *fs = NULL, *z;

	    if((z = srchstr(q, "/HN=")) != NULL)
	      hn = remove_pat_escapes(z+4);
	    if((z = srchstr(q, "/FN=")) != NULL)
	      fn = remove_pat_escapes(z+4);
	    if((z = srchstr(q, "/FS=")) != NULL)
	      fs = remove_pat_escapes(z+4);

	    hdrtok = new_hdrtok(hn);
	    if(fn)
	      hdrtok->fieldnum = atoi(fn);

	    if(fs && *fs){
		if(hdrtok->fieldseps){
		    hdrtok->fieldseps[0] = '\0';
		    hdrtok->fieldsepcnt = 0;
		}

		p = fs;
		j = 0;
		if(*p == '\"' && strchr(p+1, '\"')){
		    p++;
		    while(*p && *p != '\"'){
			if(hdrtok->fieldseps)
			  fs_resize((void **) &hdrtok->fieldseps, j+2);

			if(*p == '\\' && *(p+1))
			  p++;

			if(hdrtok->fieldseps){
			    hdrtok->fieldseps[j++] = *p++;
			    hdrtok->fieldseps[j] = '\0';
			    hdrtok->fieldsepcnt = j;
			}
		    }
		}
		else{
		    while(*p){
			if(hdrtok->fieldseps)
			  fs_resize((void **) &hdrtok->fieldseps, j+2);

			if(*p == '\\' && *(p+1))
			  p++;

			if(hdrtok->fieldseps){
			    hdrtok->fieldseps[j++] = *p++;
			    hdrtok->fieldseps[j] = '\0';
			    hdrtok->fieldsepcnt = j;
			}
		    }
		}
	    }

	    if(hn)
	      fs_give((void **)&hn);
	    if(fn)
	      fs_give((void **)&fn);
	    if(fs)
	      fs_give((void **)&fs);

	    fs_give((void **)&q);
	}
    }

    return(hdrtok);
}

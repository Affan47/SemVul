body(FILE *ifp, FILE *ofp)
{
    char  line[10000];
    char *space = " ";
    char *p;

    while(fgets(line, sizeof(line), ifp) != NULL){
	if(!strncmp(line, "====", 4)){
	    p = strtok(line, space);
	    if(p){
		p = strtok(NULL, space);
		if(p){
		    if(isalpha(*p))
		      fprintf(ofp, "extern char *%s[];\n", p);
		    else{
			fprintf(ofp, "Error: help input line\n  %s\nis bad\n", line);
			exit(-1);
		    }
		}
		else{
		    fprintf(ofp, "Error: help input\n  %scontains ==== without following helpname\n", line);
		    exit(-1);
		}

	    }
	    else{
		fprintf(ofp, "Error: help input\n  %scontains ==== without following space\n", line);
		exit(-1);
	    }
	}
    }
}

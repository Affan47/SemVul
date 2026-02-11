parse(int ac, char **av)
{
    char *pt;

    while (--ac > 0){
	pt = *(++av);
	if (*pt != '-') {
	    fprintf(stderr, "Unknown option(%s). Aborted.\n", *av);
	    exit(1);
	}else{
	    switch(*(++pt)) {
		case 't':
		    switch(*(++pt)) {
			case 'M':
			    major++;
			    break;
			case 'm':
			    minor++;
			    break;
			case 'r':
			    release++;
			    break;
			default:
			    fprintf(stderr, "Unknown -v parameter (%s). Aborted.\n", *av);
			    exit(1);
		    }
		    break;
		case 'h':
		    showhelp();
		    exit(0);
		default:
		    fprintf(stderr, "Unknown option(%s). Aborted.\n", *av);
		    exit(1);
	    }
	}
    }
}

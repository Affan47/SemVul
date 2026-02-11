print_a_line(FILE *fd, const char *line, LINENO_t num)
#else
print_a_line(fd,line,num)
	FILE *fd;
	char *line;
	LINENO_t num;
#endif
{
	(void)fprintf(fd,"\n %6u ",num);


	if(source_dec_tab) {
	  int i,col;
	  for(i=0,col=1; col < 7 && line[i] != '\0'; i++) {
	    if(line[i] == '\t') {
	      do{
		(void)fprintf(fd," ");
	      } while(++col < 7);
	    }
	    else {
		(void)fprintf(fd,"%c",line[i]);
		++col;
	    }
	  }
	  (void)fprintf(fd,"%s",line+i);
	}
	else
	  (void)fprintf(fd,"%s",line);
}

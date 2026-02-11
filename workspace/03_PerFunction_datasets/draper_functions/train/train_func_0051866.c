asm_open(char *name)
{

        int fd,i;
        int done=0;
        char string[MAX_LINE_LENGTH];
        struct stat st;
        char *next;
        int backup_line_num,backup_file_num;


        backup_line_num=source_line_num;
        backup_file_num=file_num;

        if( (include_depth++) > max_depth){
		printf("Error: maximum recursive include depth(%d) exceeded\n",max_depth);
		as_exit("");
	}
        buff[num_alloc].name=name;
        source_line_num=0;
        file_num=num_alloc;


        if ((unsigned) (fd = open(name, O_RDONLY)) > 255){
                as_exit("error opening input file\n");
        }

        if ( -1 ==  fstat( fd, &st)){
                printf("Error occured attempting to stat %s\n", name);
                as_exit("");
        }

        if(( ptralloc[num_alloc]=(char *) malloc(st.st_size+2) )== 0){
                printf("error allocating memory for file %s\n",name);
                close(fd);
                as_exit("");
        }else{
                buff[num_alloc].mem_start=ptralloc[num_alloc];

        }

        i=num_alloc;
        num_alloc++;

        buff[i].mem_end = buff[i].mem_start+st.st_size;

        read(fd, buff[i].mem_start, st.st_size);
        close(fd);

#ifdef DEBUG
  	printf("File %s opened:\n",name);
#endif


        current_line=buff[i].mem_start;
        source_line_num=1;
        next=current_line;
        while(next!=buff[i].mem_end){
                while((*next!= '\n') && (next!=buff[i].mem_end) )
                        next++;
                listtemp[0]='\0';
                *next='\0';

#ifdef DEBUG
                printf("%s\n",current_line);
#endif
                if(strlen(current_line)>MAX_LINE_LENGTH)
                        as_exit("Parse error: Line exceeds allowable limit");
                strcpy(&string[0],current_line);

                done = parse(string,current_line);
		if(listing){
			if(done==1 &&include_depth!=1)
				sprintf(listtemp,"Exiting included file");
			if(done!=-3)
				fprintf(listfile,"%-50s ||   %s\n",listtemp,current_line);
			}

		*next='\n';

                if(done==1)
			goto done;

                if(next!=buff[i].mem_end){
                        source_line_num++;
                        next++;
                }

                current_line=next;
        }

        if(done==0)
                printf("warning no END directive at end of file %s\n",name);
done:
        source_line_num=backup_line_num;
        file_num=backup_file_num;

        include_depth--;


#ifdef DEBUG
  	printf("File %s closed:\n",name);
#endif
        return;
}

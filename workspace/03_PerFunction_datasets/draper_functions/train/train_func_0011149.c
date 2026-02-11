sspm_write_mime(struct sspm_part *parts,size_t num_parts,
		    char **output_string, char* header)
{
    struct sspm_buffer buf;
    int part_num =0;

    buf.buffer = malloc(4096);
    buf.pos = buf.buffer;
    buf.buf_size = 10;
    buf.line_pos = 0;


    if(header != 0){
	sspm_append_string(&buf,header);
    }

    if(buf.buffer[strlen(buf.buffer)-1] != '\n'){
	sspm_append_char(&buf,'\n');
    }


    sspm_append_string(&buf,"MIME-Version: 1.0\n");


    while(parts[part_num].header.major != SSPM_NO_MAJOR_TYPE){
	if (parts[part_num].header.major == SSPM_MULTIPART_MAJOR_TYPE){
	    sspm_write_multipart_part(&buf,parts,&part_num);
	} else {
	    sspm_write_part(&buf, &(parts[part_num]), &part_num);
	}

	part_num++;
    }


    *output_string = buf.buffer;

    return 0;
}

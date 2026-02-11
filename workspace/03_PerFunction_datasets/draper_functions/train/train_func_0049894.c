string_line_generator(char *out, size_t buf_size, void *d)
{
    char *n;
    size_t size;
    struct slg_data* data = (struct slg_data*)d;

    if(data->pos==0){
	data->pos=data->str;
    }


    if (*(data->pos)==0){
	return 0;
    }

    n = strchr(data->pos,'\n');

    if (n == 0){
	size = strlen(data->pos);
    } else {
	n++;
	size = (n-data->pos);
    }

    if (size > buf_size-1){
	size = buf_size-1;
    }


    strncpy(out,data->pos,size);

    *(out+size) = '\0';

    data->pos += size;

    return out;
}

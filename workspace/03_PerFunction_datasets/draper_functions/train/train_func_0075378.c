check_complete(void)
{if(change_limit!=change_buffer)
{int l=(int)(change_limit-change_buffer);
strncpy(buffer,change_buffer,l);limit= &buffer[l];
changing=true;loc=buffer;web_file_open=true;

err_print("! Change file entry did not match");

}
}

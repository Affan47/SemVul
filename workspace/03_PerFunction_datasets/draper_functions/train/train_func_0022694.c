do_sftp_cleanup()
{
    char ch;
    if (back) {
	back->special(backhandle, TS_EOF);
	sftp_recvdata(&ch, 1);
	back->free(backhandle);
	sftp_cleanup_request();
	back = NULL;
	backhandle = NULL;
    }
    if (pwd) {
	sfree(pwd);
	pwd = NULL;
    }
    if (homedir) {
	sfree(homedir);
	homedir = NULL;
    }
}

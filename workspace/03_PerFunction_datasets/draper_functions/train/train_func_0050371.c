askappend(void *frontend, Filename filename,
	      void (*callback)(void *ctx, int result), void *ctx)
{
    static const char msgtemplate[] =
	"The session log file \"%.*s\" already exists.\n"
	"You can overwrite it with a new session log,\n"
	"append your session log to the end of it,\n"
	"or disable session logging for this session.\n"
	"Enter \"y\" to wipe the file, \"n\" to append to it,\n"
	"or just press Return to disable logging.\n"
	"Wipe the log file? (y/n, Return cancels logging) ";

    static const char msgtemplate_batch[] =
	"The session log file \"%.*s\" already exists.\n"
	"Logging will not be enabled.\n";

    char line[32];


    if (console_batch_mode) {
	fprintf(stderr, msgtemplate_batch, FILENAME_MAX, filename.path);
	fflush(stderr);
	return 0;
    }
    fprintf(stderr, msgtemplate, FILENAME_MAX, filename.path);
    fflush(stderr);

    {
	struct termios oldmode, newmode;
	tcgetattr(0, &oldmode);
	newmode = oldmode;
	newmode.c_lflag |= ECHO | ISIG | ICANON;
	tcsetattr(0, TCSANOW, &newmode);
	line[0] = '\0';
	int ret;
	do
	{
	    ret = read(0, line, sizeof(line) - 1);
	} while (ret == -1 && errno == EINTR);
	tcsetattr(0, TCSANOW, &oldmode);
    }


    if (line[0] == 'y' || line[0] == 'Y')
	return 2;
    else if (line[0] == 'n' || line[0] == 'N')
	return 1;
    else
	return 0;
}

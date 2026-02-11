readdirqueue(DIR *d, char *queue)
{
	struct dirent *f;
	do {
		f = readdir(d);
	} while (f && (*f->d_name == '.' || strncmp(f->d_name, queue, strlen(queue)) || f->d_name[strlen(queue)] != '.'));
	return f;
}

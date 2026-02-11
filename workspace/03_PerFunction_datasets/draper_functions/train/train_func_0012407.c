update(QIODevice *file)
{
	char buffer[1024];
	int len;

	while ((len=file->read(reinterpret_cast<char*>(buffer), sizeof(buffer))) > 0)
		update(buffer, len);
}

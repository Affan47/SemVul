exists(const char* file)
{
	fstream file_op(file,ios::in);
	if (file_op.is_open())
	{
		file_op.close();
		return true;
	}
	else return false;
}

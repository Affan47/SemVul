getOutput(void)
{
	if (this->externalOutputStream == NULL)
	{
		if (this->filename == "") {
			return cout;
		} else {
			if (outputStream == NULL)
			{
				outputStream = new ofstream(filename.c_str());
				if (outputStream == NULL)
				{
					cerr << "Can't write into file : " << filename << endl;
					exit(1);
				}
			}
			return *outputStream;
		}
	} else {
		return *this->externalOutputStream;
	}
}

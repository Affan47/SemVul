scan(std::string& str)
{
	char* endptr = (char*)str.c_str();
	FCEU_en32lsb(data,strtoul(endptr,&endptr,16));
	FCEU_en16lsb(data+4,strtoul(endptr+1,&endptr,16));
	FCEU_en16lsb(data+6,strtoul(endptr+1,&endptr,16));
	FCEU_en16lsb(data+8,strtoul(endptr+1,&endptr,16));
	endptr++;
	for(int i=0;i<6;i++)
		data[10+i] = hexToByte(&endptr);
}

read_uint8()
{
	cl_uint8 answer;
	if (read(&answer, sizeof(cl_uint8)) != sizeof(cl_uint8)) throw CL_Error("CL_InputSource_Datafile::read_uint8() failed");
	if (little_endian_mode)
	{
		SWAP_IF_BIG(answer);
	}
	else
	{
		SWAP_IF_LITTLE(answer);
	}
	return answer;
}

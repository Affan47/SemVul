writeToStream(mrpt::utils::CStream &out, int *version) const
{
	if (version)
		*version = 2;
	else
	{
		uint32_t n = x.size();


		out << n;

		if (n>0)
		{
			out.WriteBufferFixEndianness(&x[0],n);
			out.WriteBufferFixEndianness(&y[0],n);
			out.WriteBufferFixEndianness(&z[0],n);
			out.WriteBufferFixEndianness(&pointWeight[0],n);
		}

		out << genericMapParams;
		insertionOptions.writeToStream(out);
		likelihoodOptions.writeToStream(out);
	}
}

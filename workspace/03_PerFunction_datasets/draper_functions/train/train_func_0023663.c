writeToStream(mrpt::utils::CStream &out, int *out_Version) const
{
	if (out_Version)
		*out_Version = 0;
	else
	{
		uint32_t	row,col,nRec = (uint32_t) getRecordCount(), nFie=(uint32_t) fieldsCount();

		out << nRec << nFie;

		for (col=0;col<nFie;col++)
			out << field_names[col];

		for (row=0;row<nRec;row++)
			for (col=0;col<nFie;col++)
				out << data[row][col];
	}
}

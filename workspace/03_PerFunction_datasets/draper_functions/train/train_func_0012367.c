writeToStream(mrpt::utils::CStream &out,int *version) const
{
	if (version)
		*version = 0;
	else
	{
		out << mean;

		for (size_t r=0;r<size(cov_inv,1);r++)
			out << cov_inv.get_unsafe(r,r);
		for (size_t r=0;r<size(cov_inv,1);r++)
			for (size_t c=r+1;c<size(cov_inv,2);c++)
				out << cov_inv.get_unsafe(r,c);
	}
}

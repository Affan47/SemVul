readFromStream(mrpt::utils::CStream &in, int version)
{
	switch(version)
	{
	case 0:
		{
			uint32_t	i,n;

			in >> n;

			possibleTypes.clear();

			for (i=0;i<n;i++)
			{
				std::string		aux;
				in >> aux;
				possibleTypes.push_back( aux );
			}


			in >> i; selection = i;
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};
}

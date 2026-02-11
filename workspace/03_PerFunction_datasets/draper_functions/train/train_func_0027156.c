print( std::ostream& so ) const
{
	so << "--- Memory usage" << std::endl;
	so << "- physical allocated memory (in bytes):" << physalloc << std::endl;
	so << "- logical  allocated memory (in bytes):" << logalloc << std::endl;
	so << "- details for each bloc size:\n";
	so.width(7); so << "index" << ": "; so.width(9); so << "bytes" << " | ";
	so.width(9); so << "#physical" << " | "; so.width(9); so << "#logical" << std::endl;
	for (size_t i=0; i<sizetab; i++) {
		if (tabphy[i] !=0) {
			so.width(7); so << i << ": ";
			so.width(9); so << tabbloc[i] << " | " ;
			so.width(9); so << tabphy[i] << " | ";
			so.width(9); so << tablog[i] << std::endl;
		}
	}
	return so;
}

load(std::istream& is)
{


  unsigned int local_offset = 2;

  unsigned long index_size = get_entry_count() * SIZE;

  unsigned long file_offset = get_file_size() - index_size;

  is.seekg(file_offset);


  for (unsigned int entry_number = 0; entry_number < get_entry_count(); entry_number++) {
	  bsaindexentry* e = new bsaindexentry();
	  e->set_offset(local_offset);
	  try {
		  e->read(is);
	  } catch (int e) {
		  std::cerr << "Exception in bsaindexentry.read(): " << e << std::endl;
	  }

	  local_offset += e->get_size();

	  const std::string key = e->get_name();
	  entries.insert( std::pair<std::string, bsaindexentry>(key, *e) );
	  delete e;
	  e = NULL;
  }
}

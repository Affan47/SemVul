process(const Document &document)
{
  list<auto_ptr<Meta> >::const_iterator i;
  for(i = document.head.metas.begin(); i != document.head.metas.end(); ++i) {
    bool exists = false;
    get_attribute(i->get()->attributes.get(), "http-equiv", &exists);
    if (exists) {
      string content = get_attribute(i->get()->attributes.get(), "content", "");
	  char to_find[] = "charset=";
	  string::size_type found_pos = content.find(to_find);
	  if (found_pos != string::npos)
	  {
        this->meta_encoding = content.substr(found_pos + sizeof(to_find) - 1);

	  }
      break;
    }
  }

  switch (mode) {

  case PRINT_AS_ASCII:
    document.format( 0, width, Area::LEFT, os);
    break;

  case UNPARSE:
    document.unparse(os, std::endl);
    break;

  case SYNTAX_CHECK:
    break;

  default:
    std::cerr << "??? Invalid mode " << mode << " ??? " << std::endl;
    exit(1);
    break;
  }
}

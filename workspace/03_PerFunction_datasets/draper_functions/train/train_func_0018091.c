read_fasta_seq(char * filename)
{
  FILE * fp = fopen(filename, "r");
  if (fp == NULL) {
    std::cerr << "ERROR: Cannot open filename '" << filename \
	      << "' for reading.\n";
    exit(-1);
  }

  int filesize = 0;
  fseek(fp, 0, SEEK_END);
  filesize = ftell(fp);
  rewind(fp);

  if (filesize <= 0) {
    std::cerr << "ERROR: no data in file '" << filename << "'???\n";
    exit(-1);
  }


  char * buf = new char[filesize+1];


  long items_read = fread(buf, filesize, 1, fp);
  if (items_read != 1) {
    std::cerr << "ERROR: short read on file '" << filename << "'.\n";
    exit(-1);
  }
  buf[filesize] = 0;

  std::string contents(buf);

  delete buf;

  if (contents[0] != '>') {
    std::cerr << "ERROR: contents of file '" << filename \
	      << "' does not begin with a '>'.\n";
    exit(-1);
  }


  std::string::size_type pos = contents.find("\n");

  std::string name = std::string(contents, 1, pos - 1);
  std::string seq = std::string(contents, pos + 1, contents.length());


  pos = seq.find("\n");
  while (pos != std::string::npos) {
    seq.erase(pos, 1);
    pos = seq.find("\n");
  }


  if (seq.find(">") != std::string::npos) {
    std::cerr << "ERROR: file '" << filename \
	      << "' contains more than one sequence.\n";
    exit(-1);
  }

  std::cerr << "Loaded sequence '" << name << "' from file '" \
	    << filename << "'; length " << seq.length() << ".\n";

  return seq;
}

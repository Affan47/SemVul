main(int argc,char *argv[])
{
	for(int i=1;i<argc;i++) {
		string infile=argv[i];
		string::size_type pos=infile.find_last_of(".");
		string outfile=infile.substr(0,pos)+".kaw";

		ifstream ifs;
		ifs.open(infile.c_str());
		ofstream ofs;
		ofs.open(outfile.c_str());

		if((ifs.is_open())&&(ofs.is_open())) {
			string buff;
			bool cryptmode=false;
			while(getline(ifs,buff)) {
				buff=StringTrim2(buff);
				string buff2=StringTrim(buff);
				if(buff2==":crypt") {
					cryptmode=true;
				} else if(buff2==":endcrypt") {
					cryptmode=false;
				} else {
					if(!cryptmode) {
						ofs << buff << endl;
					} else {
						ofs << EncryptString(buff2) << endl;
					}
				}
			}

		}

		ifs.close();
		ofs.close();
	}

	return(0);
}

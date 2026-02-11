IP_readImage(char *file)
{

	imageP	 I;
	int	 w, h, maxGray;
   	char  	 buf[1024];
	uchar	*out;


	ifstream inFile (file, ios::binary);


	if(!inFile) {
		cerr << "readImage: Can't open " << file << endl;
		exit(1);
	}


   	inFile.getline(buf, 3);
   	if(strncmp(buf,"P5",2) && strncmp(buf,"P6",2)){
      		cerr << "The file " << file << " is not in PGM format" << endl;
      		inFile.close();
      		exit(1);
   	}


	inFile >> w >> h >> maxGray;


	inFile.getline(buf, 2);


	I = IP_allocImage(w, h, sizeof(uchar));
	out = I->image;
	inFile.read((char *) out, w*h);

	return (imageP) I;
}

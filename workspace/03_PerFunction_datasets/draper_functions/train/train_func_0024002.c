ReadImage(char* fileName,Image32& img){
	char* ext=GetFileExtension(fileName);
	int ret=0;
	if(!strcasecmp(ext,"bmp")){ret=BMPReadImage(fileName,img);}
	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGReadImage(fileName,img);}
	else {};
	delete[] ext;
	return ret;
}

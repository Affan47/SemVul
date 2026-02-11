iom_open(const char *filename,int flags,const char *model)
{

	IomFile ret(dbgnew iom_file());
	ret->setFilename(filename);
	if(iom_fileexists(filename)){

		if((flags & IOM_DONTREAD)==0){
			ret->readHeader(model);
		}
	}else{


		if((flags & IOM_CREATE)==0){
			std::string msg="File '";
			msg+=filename;
			msg+="' doesn't exist";
			iom_issueerr(msg.c_str());
			return 0;
		}
	}
	return ret->getRef();
}

read(const char *filename)
{
	String temp;
	temp = (char *) filename;
	temp.toLower();
	if (temp.endsWith(".jpg") || temp.endsWith(".jpeg")
	    || temp.endsWith(".jpe")) {
		mimetype = "image/jpg";
	}
	else if (temp.endsWith("png"))
		mimetype = "image/png";
	else {
		mimetype = "image/gif";
	}

	std::ifstream imagefile;
	imagefile.open(filename, std::ifstream::binary);
	imagefile.seekg(0, std::ios::end);
	imagelength = imagefile.tellg();
	imagefile.seekg(0, std::ios::beg);

	if (imagelength) {
		if (image != NULL)
			delete[] image;
		image = new char[imagelength + 1];
		imagefile.read(image, imagelength);
		if (!imagefile.good()) {
			if (!is_daemonised)
				std::cerr << "Error reading custom image file: " << filename << std::endl;
			syslog(LOG_ERR, "%s", "Error reading custom image file.");
			return false;
		}
	} else {
		if (!is_daemonised)
			std::cerr << "Error reading custom image file: " << filename << std::endl;
		syslog(LOG_ERR, "%s", "Error reading custom image file.");
		return false;
	}
	imagefile.close();


	return true;
}

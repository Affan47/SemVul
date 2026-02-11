substring(int index, int length){
	if ((index>=0)&&(length>0)&&((index+length)<(int)linebuf.size()))
		return linebuf.substr(index, length);
	else
		return ("");
}

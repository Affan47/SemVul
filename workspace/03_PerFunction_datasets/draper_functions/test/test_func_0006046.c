textCdIdxName(ajuint ipos, TextPCdFile fil)
{
    ajuint nameSize;

    nameSize = fil->RecSize-10;

    if(textCdMaxNameSize < nameSize)
    {
	textCdMaxNameSize = nameSize;
	if(textCdName)
	    ajCharDel(&textCdName);
	textCdName = ajCharNewRes(textCdMaxNameSize+1);
    }

    textCdFileSeek(fil, ipos);
    ajReadbinCharTrim(fil->File, nameSize, textCdName);

    return textCdName;
}

readTexture(io::IXMLReaderUTF8* reader)
{
	#ifdef COLLADA_READER_DEBUG
	os::Printer::log("COLLADA reading texture");
	#endif


	Textures.push_back(SColladaTexture());
	SColladaTexture& texture=Textures.getLast();

	texture.Id = readId(reader);

	if (!reader->isEmptyElement())
	{
		readColladaInputs(reader, textureSectionName);
		SColladaInput* input = getColladaInput(ECIS_IMAGE);
		if (input)
		{
			const core::stringc imageName = input->Source;
			texture.Texture = getTextureFromImage(imageName);
		}
	}
}

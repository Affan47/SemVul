tag_file (std::string const & filename, SessionMetadata const & metadata)
{
	TagLib::FileRef file (filename.c_str());
	TagLib::Tag & tag (*file.tag());

	tag_generic (tag, metadata);


	TagLib::FLAC::File * flac_file;
	if ((flac_file = dynamic_cast<TagLib::FLAC::File *> (file.file()))) {
		TagLib::Ogg::XiphComment * vorbis_tag;
		if ((vorbis_tag = dynamic_cast<TagLib::Ogg::XiphComment *> (flac_file->xiphComment (true)))) {
			tag_vorbis_comment (*vorbis_tag, metadata);
		} else {
			std::cerr << "Could not get Xiph comment for FLAC file!" << std::endl;
		}
	}


	TagLib::Ogg::File * ogg_file;
	if ((ogg_file = dynamic_cast<TagLib::Ogg::File *> (file.file()))) {
		TagLib::Ogg::XiphComment * vorbis_tag;
		if ((vorbis_tag = dynamic_cast<TagLib::Ogg::XiphComment *> (ogg_file->tag()))) {
			tag_vorbis_comment (*vorbis_tag, metadata);
		} else {
			std::cerr << "Could not get Xiph comment for Ogg file!" << std::endl;
		}
	}

	file.save();
	return true;
}

add_to_padding_length_(unsigned indx, int delta)
{
	FLAC::Metadata::Padding *padding = dynamic_cast<FLAC::Metadata::Padding *>(our_metadata_.blocks[indx]);
	FLAC__ASSERT(0 != padding);
	padding->set_length((unsigned)((int)padding->get_length() + delta));
}

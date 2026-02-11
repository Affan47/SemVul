seek(qpdf_offset_t offset, int whence)
{
    QUtil::os_wrapper(std::string("seek to ") + this->filename + ", offset " +
		      QUtil::int_to_string(offset) + " (" +
		      QUtil::int_to_string(whence) + ")",
		      QUtil::seek(this->file, offset, whence));
}

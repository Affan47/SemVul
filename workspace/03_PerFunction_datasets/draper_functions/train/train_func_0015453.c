set_length_in_bytes(void)
{
  off_t savetemp = fio_repp->get_file_position();
  uint32_t blksize = 0;

  find_block("data", &blksize);
  off_t datastart = fio_repp->get_file_position();

  fio_repp->set_file_position_end();
  off_t datalen = fio_repp->get_file_position() - datastart;


  if (blksize != 0 &&
      blksize != UINT32_MAX) {
    set_length_in_samples(blksize / frame_size());
  }
  else
    set_length_in_samples(datalen / frame_size());

  ECA_LOG_MSG(ECA_LOGGER::user_objects,
	      "data block length in header " +
	      kvu_numtostr(blksize) +
	      ", file length after data block " +
	      kvu_numtostr(datalen) +
	      ", length set to " +
	      kvu_numtostr(length_in_samples()) +
	      " samples");

  fio_repp->set_file_position(savetemp);
}

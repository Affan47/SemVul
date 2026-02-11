seek_position(SAMPLE_SPECS::sample_pos_t pos)
{
  if (is_open() == true) {
    off_t curpos_rep = pos * frame_size();
    DBC_CHECK(curpos_rep >= 0);

#if _FILE_OFFSET_BITS==64
    off_t seekpos = 0;
    off_t seekstep = 0;
    int whence = SEEK_SET;
    while(curpos_rep - seekpos > 0) {
      if (curpos_rep - seekpos > LONG_MAX)
	seekstep = LONG_MAX;
      else
	seekstep = curpos_rep - seekpos;


      int res = std::fseek(fobject, seekstep, whence);
      if (res != 0) {
	  ECA_LOG_MSG(ECA_LOGGER::info, "fseek() error! (lfs).");
	  curpos_rep = 0;
	  std::fseek(fobject, 0, SEEK_SET);
	  break;
      }
      if (seekpos == 0) whence = SEEK_CUR;
      seekpos += seekstep;
    }
#else
    DBC_CHECK(sizeof(long int) == sizeof(off_t));
    std::fseek(fobject, static_cast<long int>(curpos_rep), SEEK_SET);
#endif
  }

  return pos;
}

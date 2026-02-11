set_file_position(off_t newpos)
{
  curpos_rep = newpos;
  if (standard_mode != true) {

#if _FILE_OFFSET_BITS==64
    off_t seekpos = 0;
    off_t seekstep = 0;
    int whence = SEEK_SET;
    while(curpos_rep - seekpos >= 0) {
      if (curpos_rep - seekpos > LONG_MAX)
	seekstep = LONG_MAX;
      else
	seekstep = curpos_rep - seekpos;


      if (seekstep == 0 && whence == SEEK_CUR) break;


      int res = std::fseek(f1, seekstep, whence);
      if (res != 0) {
	  ECA_LOG_MSG(ECA_LOGGER::info, "(eca-fileio-stream) fseek() error! (lfs).");
	  curpos_rep = 0;
	  std::fseek(f1, 0, SEEK_SET);
	  break;
      }
      if (seekpos == 0) whence = SEEK_CUR;
      seekpos += seekstep;
    }
#else


    std::fseek(f1, static_cast<long int>(curpos_rep), SEEK_SET);
#endif
  }
}

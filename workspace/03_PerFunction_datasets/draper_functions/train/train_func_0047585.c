init(const Target *targ)
{
   for (unsigned int rf = 0; rf <= FILE_ADDRESS; ++rf) {
      DataFile f = static_cast<DataFile>(rf);
      last[rf] = targ->getFileSize(f) - 1;
      unit[rf] = targ->getFileUnit(f);
      fill[rf] = -1;
      assert(last[rf] < MAX_REGISTER_FILE_SIZE);
      bits[rf].allocate(last[rf] + 1, true);
   }
}

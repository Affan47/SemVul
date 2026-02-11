collectLineCounts(FileInfo &FI, StringRef Filename,
				  uint32_t Count) {
  for (SmallVector<uint32_t, 16>::iterator I = Lines.begin(),
	 E = Lines.end(); I != E; ++I)
    FI.addLineCount(Filename, *I, Count);
}

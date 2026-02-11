PermuteInputData(ExtendedOctree &tree, LargeRAWFile_ptr
                                               pLargeRAWFileIn, uint64_t iInOffset,
                                               bool bClampToEdge) {
  std::vector<uint8_t> vData;
  UINT64VECTOR3 baseBricks = tree.GetBrickCount(0);
  const float progress_start = m_fProgress;

  uint64_t iCurrentOutOffset = tree.ComputeHeaderSize();
  for (uint64_t z = 0;z<baseBricks.z;z++) {
    for (uint64_t y = 0;y<baseBricks.y;y++) {
      for (uint64_t x = 0;x<baseBricks.x;x++) {
        UINT64VECTOR4 coords(x,y,z,0);
        uint64_t iUncompressedBrickSize = tree.ComputeBrickSize(UINT64VECTOR4(x,y,z,0)).volume() * tree.GetComponentTypeSize() * tree.GetComponentCount();
        TOCEntry t = {iCurrentOutOffset, iUncompressedBrickSize, CT_NONE, iUncompressedBrickSize, UINTVECTOR2(0,0)};
        tree.m_vTOC.push_back(t);

        GetInputBrick(vData, tree, pLargeRAWFileIn, iInOffset, coords, bClampToEdge);
        SetBrick(&(vData[0]), tree, coords);

        iCurrentOutOffset += iUncompressedBrickSize;
        const float xf = float(x);
        const float p = xf + y*baseBricks.x + z*baseBricks.x*baseBricks.y;
        m_fProgress = MathTools::lerp(p / float(baseBricks.volume()),
                                      0.0f,1.0f, progress_start,0.4f);
      }
      PROGRESS;
    }
  }
}

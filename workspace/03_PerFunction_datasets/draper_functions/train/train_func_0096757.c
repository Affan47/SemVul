DetermineNumberOfTimesteps()
{
  size_t toc=0, raster=0, hist1d=0, hist2d=0, accel=0;
  bool is_color = false;
  for(size_t block=0; block < m_pDatasetFile->GetDataBlockCount(); ++block) {
    switch(m_pDatasetFile->GetDataBlock(block)->GetBlockSemantic()) {
      case UVFTables::BS_1D_HISTOGRAM: hist1d++; break;
      case UVFTables::BS_2D_HISTOGRAM: hist2d++; break;
      case UVFTables::BS_MAXMIN_VALUES: accel++; break;
      case UVFTables::BS_REG_NDIM_GRID:
        {
          const RasterDataBlock *rdb =
            static_cast<const RasterDataBlock*>
                       (m_pDatasetFile->GetDataBlock(block));
          if(VerifyRasterDataBlock(rdb)) {
            ++raster;
            if (rdb->ulElementDimensionSize[0] == 4 ||
                rdb->ulElementDimensionSize[0] == 3) {
              is_color = true;
            }
          }
        }
        break;
      case UVFTables::BS_TOC_BLOCK:
        {
          const TOCBlock *tb =
            static_cast<const TOCBlock*>
                       (m_pDatasetFile->GetDataBlock(block));
          if(VerifyTOCBlock(tb)) {
            ++toc;
            if (tb->GetComponentCount() == 4 || tb->GetComponentCount() == 3) {
              is_color = true;
            }
          }
        }
        break;
      default: break;
    }
  }
  MESSAGE("Block counts (toc, raster, hist1, hist2, accel): (%u, %u, %u, %u, %u)",
          static_cast<unsigned>(toc),
          static_cast<unsigned>(raster),
          static_cast<unsigned>(hist1d),
          static_cast<unsigned>(hist2d),
          static_cast<unsigned>(accel));

  if (toc > raster) m_bToCBlock = true;


  if(is_color) {
    return std::max(raster,toc);
  }
  if(raster+toc == hist1d && hist1d == hist2d && hist2d == accel) {
    return std::max(raster,toc);
  }

  T_ERROR("UVF Block combinations do not match; "
          "do not know how to interpret data.  "
          "Block counts (toc, raster, hist1, hist2, accel): (%u, %u, %u, %u, %u)",
          static_cast<unsigned>(toc),
          static_cast<unsigned>(raster),
          static_cast<unsigned>(hist1d),
          static_cast<unsigned>(hist2d),
          static_cast<unsigned>(accel));
  throw tuvok::io::DSParseFailed("No valid timesteps in UVF!");
}

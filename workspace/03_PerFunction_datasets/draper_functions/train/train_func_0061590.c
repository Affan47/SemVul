CreateDeviantPaths(
    boost::shared_ptr<const ChartTrellisPath> basePath,
    ChartTrellisDetourQueue &q)
{
  CreateDeviantPaths(basePath, basePath->GetFinalNode(), q);
}

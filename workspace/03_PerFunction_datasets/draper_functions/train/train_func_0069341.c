GetPartBlockInfo(int idx)
{
  char buffer[80];
  vtkStdString blocks;
  std::vector<int> blkIndices = this->PartInfo[idx].BlockIndices;
  for (unsigned int i=0;i<blkIndices.size();i++)
    {
    sprintf(buffer,"%d, ",blkIndices[i]);
    blocks += buffer;
    }

  blocks.erase(blocks.size()-2,blocks.size()-1);

  return blocks.c_str();
}

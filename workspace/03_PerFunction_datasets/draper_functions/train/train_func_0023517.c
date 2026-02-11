NewPartitioningRequest(int req)
{
  if (req != this->ValidDirections)
    {
    this->Modified();
    this->ValidDirections = req;
    }
}

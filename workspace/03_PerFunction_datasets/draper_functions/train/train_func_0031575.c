GetStatusEntries()
{
  this->DatabaseProxy->Open();
  std::vector<midasStatus> stats = this->DatabaseProxy->GetStatusEntries();
  this->DatabaseProxy->Close();
  return stats;
}

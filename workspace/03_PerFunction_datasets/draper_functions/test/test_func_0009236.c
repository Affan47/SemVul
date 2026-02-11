WriteCheckpoint(int index)
{
  std::string fname = this->CTest->GetBinaryDir()
    + "/Testing/Temporary/CTestCheckpoint.txt";
  std::fstream fout;
  fout.open(fname.c_str(), std::ios::app | std::ios::out);
  fout << index << "\n";
  fout.close();
}

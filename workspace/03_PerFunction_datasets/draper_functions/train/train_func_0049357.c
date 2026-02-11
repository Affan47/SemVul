CreateTestCostList()
{
  for(TestMap::iterator i = this->Tests.begin();
      i != this->Tests.end(); ++i)
    {
    std::string name = this->Properties[i->first]->Name;
    if(std::find(this->LastTestsFailed.begin(), this->LastTestsFailed.end(),
       name) != this->LastTestsFailed.end())
      {
      this->TestCosts[FLT_MAX].insert(i->first);
      }
    else
      {
      this->TestCosts[this->Properties[i->first]->Cost].insert(i->first);
      }
    }
}

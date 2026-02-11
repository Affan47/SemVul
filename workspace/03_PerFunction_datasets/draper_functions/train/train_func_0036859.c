CheckCycles()
{
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
             "Checking test dependency graph..." << std::endl);
  for(TestMap::iterator it = this->Tests.begin();
      it != this->Tests.end(); ++it)
    {

    int root = it->first;
    std::set<int> visited;
    std::stack<int> s;
    s.push(root);
    while(!s.empty())
      {
      int test = s.top();
      s.pop();
      if(visited.insert(test).second)
        {
        for(TestSet::iterator d = this->Tests[test].begin();
            d != this->Tests[test].end(); ++d)
          {
          if(*d == root)
            {

            cmCTestLog(this->CTest, ERROR_MESSAGE,
                       "Error: a cycle exists in the test dependency graph "
                       "for the test \"" << this->Properties[root]->Name <<
                       "\".\nPlease fix the cycle and run ctest again.\n");
            return false;
            }
          else
            {
            s.push(*d);
            }
          }
        }
      }
    }
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
             "Checking test dependency graph end" << std::endl);
  return true;
}

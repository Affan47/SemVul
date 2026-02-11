PopPolicyBarrier(bool reportError)
{

  PolicyStackType::size_type barrier = this->PolicyBarriers.back();
  while(this->PolicyStack.size() > barrier)
    {
    if(reportError)
      {
      this->IssueMessage(cmake::FATAL_ERROR,
                         "cmake_policy PUSH without matching POP");
      reportError = false;
      }
    this->PopPolicy();
    }


  this->PolicyBarriers.pop_back();
}

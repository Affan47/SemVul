SelectParts(std::set<cmCTest::Part> const& parts)
{

  for(cmCTest::Part p = cmCTest::PartStart;
      p != cmCTest::PartCount; p = cmCTest::Part(p+1))
    {
    this->SubmitPart[p] =
      (std::set<cmCTest::Part>::const_iterator(parts.find(p)) != parts.end());
    }
}

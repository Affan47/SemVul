CollectDepends()
{

  this->InitialGraph.resize(this->Targets.size());


  for(unsigned int i=0; i < this->Targets.size(); ++i)
    {
    this->CollectTargetDepends(i);
    }
}

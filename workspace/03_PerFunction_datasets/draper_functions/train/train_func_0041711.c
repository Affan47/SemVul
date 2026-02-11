ClearGeneratorTargets()
{
  for(cmGeneratorTargetsType::iterator i = this->GeneratorTargets.begin();
      i != this->GeneratorTargets.end(); ++i)
    {
    delete i->second;
    }
  this->GeneratorTargets.clear();
}

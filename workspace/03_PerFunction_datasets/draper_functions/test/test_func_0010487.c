PushScope()
{

  std::vector<DefinitionMap>::size_type index = this->DefinitionStack.size();


  this->DefinitionStack.push_back(DefinitionMap());


  this->DefinitionStack[index] = this->DefinitionStack[index-1];
}

FillCacheManagerFromUI()
{
  int size = this->Entries->size();
  for(int i=0; i < size; i++)
    {
    cmCacheManager::CacheIterator it =
      this->CMakeInstance->GetCacheManager()->GetCacheIterator(
        (*this->Entries)[i]->Key.c_str());
    if (!it.IsAtEnd())
      {
      std::string oldValue = it.GetValue();
      std::string newValue = (*this->Entries)[i]->Entry->GetValue();
      std::string fixedOldValue;
      std::string fixedNewValue;
      this->FixValue(it.GetType(), oldValue, fixedOldValue);
      this->FixValue(it.GetType(), newValue, fixedNewValue);

      if(!(fixedOldValue == fixedNewValue))
        {

        it.SetProperty("MODIFIED", true);
        it.SetValue(fixedNewValue.c_str());
        }
      }
    }
}

isModified(unsigned int address)
{
  unsigned int uIndex = cpu->map_pm_address2index(address);

  if((uIndex < cpu->program_memory_size()) &&
     cpu->program_memory[uIndex]->bIsModified())
    return true;

  return false;
}

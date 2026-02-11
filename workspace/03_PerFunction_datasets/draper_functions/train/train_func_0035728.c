ReadFromFile(std::fstream &file)
{
  const size_t memAlloc = sizeof(UINT64) + sizeof(char);
  char mem[sizeof(UINT64) + sizeof(char)];
  file.read(mem, memAlloc);

  size_t memUsed = ReadFromMemory(mem);
  CHECK(memAlloc == memUsed);

  return memAlloc;
}

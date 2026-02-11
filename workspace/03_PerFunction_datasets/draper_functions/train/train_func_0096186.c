is_empty(uint32_t index)
{
  return
    bookpos[index].key    == 0 &&
    bookpos[index].wins   == 0 &&
    bookpos[index].draws  == 0 &&
    bookpos[index].losses == 0;
}

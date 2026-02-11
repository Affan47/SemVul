eio_activate_part_part
  (int& part, int& info)
{
  if(partitioningWriter->activatePart(part) != -1)
    info = 0;
  else
    info = -1;
}

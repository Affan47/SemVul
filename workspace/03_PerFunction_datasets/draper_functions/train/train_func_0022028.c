go_forward()
{
  if(linear_index + 1 < linear_length) {
    linear_index++;
    return true;
  } else
    return false;
}

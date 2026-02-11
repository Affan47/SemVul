check_mul (int x, int y)
{
  if (x >= 0)
    {
      if (y >= 0)
	return check_pos_mul (x, y);
      else
	return -check_pos_mul (x, -y);
    }
  else if (y >= 0)
    return -check_pos_mul (-x, y);
  else
    return check_pos_mul (-x, -y);
}

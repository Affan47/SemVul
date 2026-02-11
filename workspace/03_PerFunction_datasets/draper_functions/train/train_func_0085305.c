gettoken(ARTNUM artnum, TOKEN *token) {
  int	i, j, offset, limit;
  offset = 0;
  limit = Gibcount;
  for (i = (limit - offset) / 2 ; i > 0 ; i = (limit - offset) / 2) {
    if (Gib[offset + i].artnum == artnum) {
      *token = Gib[offset + i].token;
      return true;
    } else if (Gib[offset + i].artnum == 0) {

      for (j = offset + i - 1; j >= offset ; j --) {
	if (Gib[j].artnum != 0)
	  break;
      }
      if (j < offset) {

	return false;
      }
      if (Gib[j].artnum == artnum) {
	*token = Gib[j].token;
	return true;
      } else if (Gib[j].artnum < artnum) {

	offset += i + 1;
      } else {

	limit = j;
      }
    } else if (Gib[offset + i].artnum < artnum) {

      offset += i + 1;
    } else {

      limit = offset + i;
    }
  }

  if (Gib[offset].artnum != artnum) {

    return false;
  }
  *token = Gib[offset].token;
  return true;
}

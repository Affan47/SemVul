string_to_mp (NODE_T * p, MP_T * z, char *s, int digits)
{
  int i, j, sign, weight, sum, comma, power;
  int expo;
  BOOL_T ok = A68_TRUE;
  RESET_ERRNO;
  SET_MP_ZERO (z, digits);
  while (IS_SPACE (s[0])) {
    s++;
  }

  sign = (s[0] == '-' ? -1 : 1);
  if (s[0] == '+' || s[0] == '-') {
    s++;
  }

  while (s[0] == '0') {
    s++;
  }
  i = 0;
  j = 1;
  sum = 0;
  comma = -1;
  power = 0;
  weight = MP_RADIX / 10;
  while (s[i] != NULL_CHAR && j <= digits && (IS_DIGIT (s[i]) || s[i] == POINT_CHAR)) {
    if (s[i] == POINT_CHAR) {
      comma = i;
    } else {
      int value = (int) s[i] - (int) '0';
      sum += weight * value;
      weight /= 10;
      power++;
      if (weight < 1) {
        MP_DIGIT (z, j++) = (MP_T) sum;
        sum = 0;
        weight = MP_RADIX / 10;
      }
    }
    i++;
  }

  if (j <= digits) {
    MP_DIGIT (z, j++) = (MP_T) sum;
  }

  expo = 0;
  if (s[i] != NULL_CHAR && TO_UPPER (s[i]) == TO_UPPER (EXPONENT_CHAR)) {
    char *end;
    expo = (int) strtol (&(s[++i]), &end, 10);
    ok = (BOOL_T) (end[0] == NULL_CHAR);
  } else {
    ok = (BOOL_T) (s[i] == NULL_CHAR);
  }

  expo += (comma >= 0 ? comma - 1 : power - 1);
  (void) align_mp (z, &expo, digits);
  MP_EXPONENT (z) = (MP_DIGIT (z, 1) == 0 ? 0 : (double) expo);
  MP_DIGIT (z, 1) *= sign;
  CHECK_MP_EXPONENT (p, z);
  if (errno == 0 && ok) {
    return (z);
  } else {
    return (NO_MP);
  }
}

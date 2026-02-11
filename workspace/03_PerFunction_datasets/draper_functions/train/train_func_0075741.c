static_compare_angle (const void *a, const void *b)
{
int *sequence_a = (int *) a;
int *sequence_b = (int *) b;


if (sequence_a[0] > sequence_b[0]) return 1;

if (sequence_a[0] == sequence_b[0])
  {
  if (sequence_a[1] > sequence_b[1]) return 1;

  if (sequence_a[1] == sequence_b[1])
    {
    if (sequence_a[2] > sequence_b[2]) return 1;
    }
  }


return -1;
}

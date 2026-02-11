static_wigner_replicas (int *replicas,
int *equal, int position, int node_min, int *offset)
{
int n_replicas, node;
int i, j, k;
int i_min, j_min, k_min;


n_replicas = 0;
for (node = 0; node < 8; node++)
  if (node > node_min && equal[node] == node_min)
    n_replicas++;


replicas = (int *) realloc (replicas,
(*offset + 1 + 3 * n_replicas) * sizeof (int));

replicas[position] = *offset;
replicas[(*offset)++] = n_replicas;


i_min = j_min = k_min = -1;


for (k = 0; k <= 1; k++)
  {
  for (j = 0; j <= 1; j++)
    {
    for (i = 0; i <= 1; i++)
      {
      node = 4*k + 2*j + i;

      if (node == node_min)
        {
        i_min = i;
        j_min = j;
        k_min = k;
        }

      if (node > node_min && equal[node] == node_min)
        {
        replicas [(*offset)++] = i - i_min;
        replicas [(*offset)++] = j - j_min;
        replicas [(*offset)++] = k - k_min;
        }

      }
    }
  }

return replicas;
}

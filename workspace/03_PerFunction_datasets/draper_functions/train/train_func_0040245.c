setCollider (int i, int j, dColliderFn *fn)
{
  if (colliders[i][j].fn == 0) {
    colliders[i][j].fn = fn;
    colliders[i][j].reverse = 0;
  }
  if (colliders[j][i].fn == 0) {
    colliders[j][i].fn = fn;
    colliders[j][i].reverse = 1;
  }
}

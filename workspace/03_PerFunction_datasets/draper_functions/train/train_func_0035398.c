Vector_Mod_Value(Vector vec, int n)
{
  Vector aux_vec;
  int vec_elem;
  int x;

  Vector_Allocate(aux_vec);
  Vector_Copy(aux_vec, vec);
  Vector_Empty(vec);

  if (n == 0)
    return;

  VECTOR_BEGIN_ENUM(aux_vec, vec_elem);

  x = vec_elem % n;
  if ((unsigned) x <= (unsigned) vec_max_integer)
    Vector_Set_Value(vec, x);

  VECTOR_END_ENUM;
}

vector_copy(numint_t* q2, numint_t* q1, size_t size)
{
  size_t i;
  for (i=0; i<size; i++){
    numint_set(q2[i],q1[i]);
  }
}

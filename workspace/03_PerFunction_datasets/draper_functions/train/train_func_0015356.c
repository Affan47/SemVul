pop(void)
{
  jmp_t j = jmp_head;
  if (j) jmp_head = j->next;
#ifdef DEBUG
  depth--;
#endif
  return j;
}

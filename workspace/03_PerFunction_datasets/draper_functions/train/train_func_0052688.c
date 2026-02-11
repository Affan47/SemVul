list_contains_element(list *haystack, void *needle)
{
  size_t index = 0;
  while (index < haystack->nof_elements_stored)
  {
    if (haystack->elements[index] == needle)
      return true;
    index++;
  }
  return false;
}

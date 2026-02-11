city_list_find_number(struct city_list *This, int id)
{
  if (id != 0) {
    city_list_iterate(This, pcity) {
      if (pcity->id == id) {
	return pcity;
      }
    } city_list_iterate_end;
  }

  return NULL;
}

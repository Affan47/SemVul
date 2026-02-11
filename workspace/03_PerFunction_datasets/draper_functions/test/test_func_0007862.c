flickcurl_free_place(flickcurl_place *place)
{
  int i;

  FLICKCURL_ASSERT_OBJECT_POINTER_RETURN(place, flickcurl_place);

  for(i = 0; i <= FLICKCURL_PLACE_LAST; i++) {
    if(place->names[i])
      free(place->names[i]);
    if(place->ids[i])
      free(place->ids[i]);
    if(place->urls[i])
      free(place->urls[i]);
    if(place->woe_ids[i])
      free(place->woe_ids[i]);
  }

  if(place->shape)
    flickcurl_free_shape(place->shape);

  if(place->timezone)
    free(place->timezone);

  free(place);
}

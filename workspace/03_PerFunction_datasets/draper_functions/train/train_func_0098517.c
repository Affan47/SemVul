owl_proper_eye(int pos)
{
  ASSERT_ON_BOARD1(pos);

  return ((current_owl_data->my_eye[pos].color
	   == current_owl_data->color)
	  && !current_owl_data->my_eye[pos].marginal);
}

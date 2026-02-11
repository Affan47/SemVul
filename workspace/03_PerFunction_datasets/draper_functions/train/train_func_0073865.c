ply_describe_other_elements (
  PlyFile *plyfile,
  PlyOtherElems *other_elems
)
{
  int i;
  OtherElem *other;


  if (other_elems == NULL)
    return;


  plyfile->other_elems = other_elems;


  for (i = 0; i < other_elems->num_elems; i++) {
    other = &(other_elems->other_list[i]);
    vtkPLY::ply_element_count (plyfile, other->elem_name, other->elem_count);
    vtkPLY::ply_describe_other_properties (plyfile, other->other_props,
                                   offsetof(OtherData,other_props));
  }
}

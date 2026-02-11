tile_type_num_tiles(const struct cm_tile_type *type)
{
  if (type->is_specialist) {
    return FC_INFINITY;
  } else {
    return tile_vector_size(&type->tiles);
  }
}

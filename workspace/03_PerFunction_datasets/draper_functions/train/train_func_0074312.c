write_ascii_item(
  FILE *fp,
  int int_val,
  unsigned int uint_val,
  double double_val,
  int type
)
{
  switch (type) {
    case PLY_CHAR:
    case PLY_SHORT:
    case PLY_INT:
      fprintf (fp, "%d ", int_val);
      break;
    case PLY_UCHAR:
    case PLY_USHORT:
    case PLY_UINT:
      fprintf (fp, "%u ", uint_val);
      break;
    case PLY_FLOAT:
    case PLY_DOUBLE:
      fprintf (fp, "%g ", double_val);
      break;
    default:
		throw std::runtime_error(format("write_ascii_item: bad type = %d", type));
  }
}

picture_start_code_name (guint8 psc)
{
  guint i;
  const struct
  {
    guint8 psc;
    const gchar *name;
  } psc_names[] = {
    {
    0x00, "Picture Start"}, {
    0xb0, "Reserved"}, {
    0xb1, "Reserved"}, {
    0xb2, "User Data Start"}, {
    0xb3, "Sequence Header Start"}, {
    0xb4, "Sequence Error"}, {
    0xb5, "Extension Start"}, {
    0xb6, "Reserved"}, {
    0xb7, "Sequence End"}, {
    0xb8, "Group Start"}, {
    0xb9, "Program End"}
  };
  if (psc < 0xB0 && psc > 0)
    return "Slice Start";

  for (i = 0; i < G_N_ELEMENTS (psc_names); i++)
    if (psc_names[i].psc == psc)
      return psc_names[i].name;

  return "UNKNOWN";
}

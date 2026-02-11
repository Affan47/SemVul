enter_group_data(s48_call_t call, struct group *data)
{
  s48_ref_t sch_data, members, temp;
  int length;
  char **names;

  for(length = 0, names = data->gr_mem; *names != NULL; length++, names++);
  members = s48_make_vector_2(call, length, s48_false_2(call));
  for(length = 0, names = data->gr_mem; *names != NULL; length++, names++) {
    temp = s48_enter_byte_string_2(call, *names);
    s48_unsafe_vector_set_2(call, members, length, temp);
  }

  sch_data = s48_null_2(call);
  sch_data = s48_cons_2(call, members, sch_data);
  temp = s48_enter_gid(call, data->gr_gid);
  sch_data = s48_cons_2(call, temp, sch_data);
  temp = s48_enter_byte_string_2(call, data->gr_name);
  sch_data = s48_cons_2(call, temp, sch_data);

  return sch_data;
}

get_city_citizen_types(struct city *pcity, enum citizen_feeling index,
			   enum citizen_category *citizens)
{
  int i = 0, n;
  fc_assert(index >= 0 && index < FEELING_LAST);

  for (n = 0; n < pcity->feel[CITIZEN_HAPPY][index]; n++, i++) {
    citizens[i] = CITIZEN_HAPPY;
  }
  for (n = 0; n < pcity->feel[CITIZEN_CONTENT][index]; n++, i++) {
    citizens[i] = CITIZEN_CONTENT;
  }
  for (n = 0; n < pcity->feel[CITIZEN_UNHAPPY][index]; n++, i++) {
    citizens[i] = CITIZEN_UNHAPPY;
  }
  for (n = 0; n < pcity->feel[CITIZEN_ANGRY][index]; n++, i++) {
    citizens[i] = CITIZEN_ANGRY;
  }

  specialist_type_iterate(sp) {
    for (n = 0; n < pcity->specialists[sp]; n++, i++) {
      citizens[i] = CITIZEN_SPECIALIST + sp;
    }
  } specialist_type_iterate_end;

  if (city_size_get(pcity) != i) {
    log_error("get_city_citizen_types() %d citizens "
              "not equal %d city size in \"%s\".",
              i, city_size_get(pcity), city_name(pcity));
  }
  return i;
}

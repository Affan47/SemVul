new_elan(const char *name)
{
  elan_arr[no_elans] = (Elan_t *)mem_alloc(COMP_NAME, sizeof(Elan_t));
  if (!elan_arr[no_elans]) {
    return NULL;
  }
  memset(elan_arr[no_elans],0,sizeof(Elan_t));
  elan_arr[no_elans]->elan_name_size = MIN(32, strlen(name));
  strncpy(elan_arr[no_elans]->elan_name, name,
	  elan_arr[no_elans]->elan_name_size);

  elan_arr[no_elans]->type = LE_LAN_TYPE_UNSPECIFIED;
  elan_arr[no_elans]->max_frame = LE_MAX_FRAME_UNSPECIFIED;
  return elan_arr[no_elans++];
}

get_address_by_location(uint32_t address_32) {
  map<uint32_t, vector<Address*>*>::iterator a = space_.upper_bound(address_32);
  if(a == space_.begin()) return NULL;
  --a;
  if(a->first + a->second->size() > address_32)
    return (*a->second)[address_32 - a->first];
  else
    return NULL;
}

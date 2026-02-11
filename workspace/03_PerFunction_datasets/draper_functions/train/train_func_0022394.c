stun_adjust_allocate_lifetime(turn_time_t lifetime, turn_time_t max_lifetime) {

  if(!lifetime) lifetime = STUN_DEFAULT_ALLOCATE_LIFETIME;
  else if(lifetime<STUN_MIN_ALLOCATE_LIFETIME) lifetime = STUN_MIN_ALLOCATE_LIFETIME;
  else if(lifetime>STUN_MAX_ALLOCATE_LIFETIME) lifetime = STUN_MAX_ALLOCATE_LIFETIME;

  if(max_lifetime && (max_lifetime < lifetime)) {
  	lifetime = max_lifetime;
  }

  return lifetime;
}

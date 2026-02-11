Knife_ProjectSource (gclient_t * client, vec3_t point, vec3_t distance,
		     vec3_t forward, vec3_t right, vec3_t result)
{
  vec3_t _distance;

  VectorCopy (distance, _distance);
  if (client->pers.hand == LEFT_HANDED)
    _distance[1] *= -1;
  else if (client->pers.hand == CENTER_HANDED)
    _distance[1] = 0;
  G_ProjectSource (point, _distance, forward, right, result);
}

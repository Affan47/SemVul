trajectory_destroy(Trajectory *t) {
  if(t->name != NULL) free(t->name);
  if(t->pattern != NULL) free(t->pattern);

  if(t->object != NULL && --t->object->count < 1 && t->object->tracelen == 0) {
	object_destroy(t->object);
  }
  REMOVE(t);
}

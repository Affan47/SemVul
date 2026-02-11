unregister_idle_object(Object *o)
{
	int c = idle_objs->count();
	for (int i=0; i < c; i++) if ((*idle_objs)[i] == o) {
		idle_objs->remove(idle_objs->findByIdx(i));
	}
}

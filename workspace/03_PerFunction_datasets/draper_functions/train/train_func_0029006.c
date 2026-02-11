get_free_id(IrmoWorld *world, IrmoObjectID *id)
{
	IrmoObjectID start = world->lastid;


	do {
		world->lastid = (world->lastid + 1) % MAX_OBJECTS;


		if (world->lastid == start) {
			return 0;
                }

	} while (irmo_hash_table_lookup(world->objects,
				        IRMO_POINTER_KEY(world->lastid)));

        *id = world->lastid;

        return 1;
}

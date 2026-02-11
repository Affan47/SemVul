v4_upgrade_objects()
{
    Objid oid, log_oid;
    Objid size = dbv4_last_used_objid() + 1;

    oklog("UPGRADING objects to new structure ...\n");

#   define PROGRESS_INTERVAL 10000
#   define MAYBE_LOG_PROGRESS					\
    {								\
        if (oid == log_oid) {					\
	    log_oid += PROGRESS_INTERVAL;			\
	    oklog("UPGRADE: Done through #%d ...\n", oid);	\
	}							\
    }

    for (oid = 0, log_oid = PROGRESS_INTERVAL; oid < size; oid++) {
	Object4 *o = dbv4_find_object(oid);

	MAYBE_LOG_PROGRESS;
	if (o) {
	    Object *new = dbpriv_new_object();
	    new->name = o->name;
	    new->flags = o->flags;

	    new->owner = o->owner;

	    Objid iter;

	    new->parents = var_dup(new_obj(o->parent));

	    new->children = new_list(0);
	    for (iter = o->child; iter != NOTHING; iter = objects[iter]->sibling)
		new->children = listappend(new->children, var_dup(new_obj(iter)));

	    new->location = var_dup(new_obj(o->location));

	    new->contents = new_list(0);
	    for (iter = o->contents; iter != NOTHING; iter = objects[iter]->next)
		new->contents = listappend(new->contents, var_dup(new_obj(iter)));

	    new->verbdefs = o->verbdefs;
	    new->propdefs = o->propdefs;
	    new->propval = o->propval;
	}
	else {
	    dbpriv_new_recycled_object();
	}
    }

#   undef PROGRESS_INTERVAL
#   undef MAYBE_LOG_PROGRESS

    for (oid = 0; oid < size; oid++) {
	if (objects[oid]) {
	    myfree(objects[oid], M_OBJECT);
	    objects[oid] = 0;
	}
    }

    num_objects = 0;
    max_objects = 0;
    myfree(objects, M_OBJECT_TABLE);

    oklog("UPGRADING objects to new structure ... finished.\n");
    return 1;
}

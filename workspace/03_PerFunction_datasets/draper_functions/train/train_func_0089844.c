protgroup_delete(struct protgroup *group, struct protstream *item)
{
    unsigned i;

    assert(group);
    assert(item);


    for (i = 0; i < group->next_element; i++) {
	if (group->group[i] == item) {

	    group->next_element--;
	    for (; i < group->next_element; i++) {
		group->group[i] = group->group[i+1];
	    }
	    group->group[i] = NULL;
	    return;
	}
    }
    syslog(LOG_ERR, "protgroup_delete(): can't find protstream in group");
}

tomoyo_number_matches_group(const unsigned long min,
				 const unsigned long max,
				 const struct tomoyo_group *group)
{
	struct tomoyo_number_group *member;
	bool matched = false;
	list_for_each_entry_rcu(member, &group->member_list, head.list) {
		if (member->head.is_deleted)
			continue;
		if (min > member->number.values[1] ||
		    max < member->number.values[0])
			continue;
		matched = true;
		break;
	}
	return matched;
}

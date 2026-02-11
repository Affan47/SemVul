board_group_addlib(struct board *board, group_t group, coord_t coord)
{
	if (DEBUGL(7)) {
		fprintf(stderr, "Group %d[%s] %d: Adding liberty %s\n",
			group_base(group), coord2sstr(group_base(group), board),
			board_group_info(board, group).libs, coord2sstr(coord, board));
	}

	check_libs_consistency(board, group);

	struct group *gi = &board_group_info(board, group);
	bool onestone = group_is_onestone(board, group);
	if (gi->libs < GROUP_KEEP_LIBS) {
		for (int i = 0; i < GROUP_KEEP_LIBS; i++) {
#if 0

			if (!gi->lib[i])
				break;
#endif
			if (unlikely(gi->lib[i] == coord))
				return;
		}
		if (gi->libs == 0) {
			board_capturable_add(board, group, coord, onestone);
		} else if (gi->libs == 1) {
			board_capturable_rm(board, group, gi->lib[0], onestone);
			board_atariable_add(board, group, gi->lib[0], coord);
		} else if (gi->libs == 2) {
			board_atariable_rm(board, group, gi->lib[0], gi->lib[1]);
		}
		gi->lib[gi->libs++] = coord;
	}

	check_libs_consistency(board, group);
}

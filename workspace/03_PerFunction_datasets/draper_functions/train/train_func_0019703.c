__archive_rb_tree_removal_rebalance(struct archive_rb_tree *rbt,
    struct archive_rb_node *parent, unsigned int which)
{

	while (RB_BLACK_P(parent->rb_nodes[which])) {
		unsigned int other = which ^ RB_DIR_OTHER;
		struct archive_rb_node *brother = parent->rb_nodes[other];


		if (RB_BLACK_P(parent)
		    && RB_BLACK_P(brother->rb_left)
		    && RB_BLACK_P(brother->rb_right)) {
			if (RB_RED_P(brother)) {


				__archive_rb_tree_reparent_nodes(parent, other);
				brother = parent->rb_nodes[other];
			} else {


				RB_MARK_RED(brother);
				if (RB_ROOT_P(rbt, parent))
					return;
				which = RB_POSITION(parent);
				parent = RB_FATHER(parent);
				continue;
			}
		}


		if (RB_RED_P(parent)
		    && RB_BLACK_P(brother)
		    && RB_BLACK_P(brother->rb_left)
		    && RB_BLACK_P(brother->rb_right)) {


			RB_MARK_BLACK(parent);
			RB_MARK_RED(brother);
			break;
		} else {


			if (RB_BLACK_P(brother->rb_nodes[other])) {


				__archive_rb_tree_reparent_nodes(brother, which);
				brother = parent->rb_nodes[other];
			}


			RB_MARK_BLACK(brother->rb_nodes[other]);
			__archive_rb_tree_reparent_nodes(parent, other);
			break;
		}
	}
}

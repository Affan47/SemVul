__add_reloc_root(struct btrfs_root *root)
{
	struct rb_node *rb_node;
	struct mapping_node *node;
	struct reloc_control *rc = root->fs_info->reloc_ctl;

	node = kmalloc(sizeof(*node), GFP_NOFS);
	if (!node)
		return -ENOMEM;

	node->bytenr = root->node->start;
	node->data = root;

	spin_lock(&rc->reloc_root_tree.lock);
	rb_node = tree_insert(&rc->reloc_root_tree.rb_root,
			      node->bytenr, &node->rb_node);
	spin_unlock(&rc->reloc_root_tree.lock);
	if (rb_node) {
		btrfs_panic(root->fs_info, -EEXIST, "Duplicate root found "
			    "for start=%llu while inserting into relocation "
			    "tree", node->bytenr);
		kfree(node);
		return -EEXIST;
	}

	list_add_tail(&root->root_list, &rc->reloc_roots);
	return 0;
}

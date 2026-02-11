inode_switch_wbs(struct inode *inode, int new_wb_id)
{
	struct backing_dev_info *bdi = inode_to_bdi(inode);
	struct cgroup_subsys_state *memcg_css;
	struct inode_switch_wbs_context *isw;


	if (inode->i_state & I_WB_SWITCH)
		return;

	isw = kzalloc(sizeof(*isw), GFP_ATOMIC);
	if (!isw)
		return;


	rcu_read_lock();
	memcg_css = css_from_id(new_wb_id, &memory_cgrp_subsys);
	if (memcg_css)
		isw->new_wb = wb_get_create(bdi, memcg_css, GFP_ATOMIC);
	rcu_read_unlock();
	if (!isw->new_wb)
		goto out_free;


	spin_lock(&inode->i_lock);
	if (!(inode->i_sb->s_flags & MS_ACTIVE) ||
	    inode->i_state & (I_WB_SWITCH | I_FREEING) ||
	    inode_to_wb(inode) == isw->new_wb) {
		spin_unlock(&inode->i_lock);
		goto out_free;
	}
	inode->i_state |= I_WB_SWITCH;
	spin_unlock(&inode->i_lock);

	ihold(inode);
	isw->inode = inode;

	atomic_inc(&isw_nr_in_flight);


	call_rcu(&isw->rcu_head, inode_switch_wbs_rcu_fn);
	return;

out_free:
	if (isw->new_wb)
		wb_put(isw->new_wb);
	kfree(isw);
}

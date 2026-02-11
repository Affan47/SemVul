au_symlink_del(struct super_block *sb, struct au_symlink *slink)
{
	struct au_sbinfo *sbinfo;


	iput(slink->h_inode);
	slink->h_inode = NULL;
	sbinfo = au_sbi(sb);
	au_sphl_del_rcu(&slink->hlist, &sbinfo->si_symlink);
	kfree_rcu(slink, rcu);
}

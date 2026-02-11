ext4_es_free_extent(struct inode *inode, struct extent_status *es)
{
	EXT4_I(inode)->i_es_all_nr--;
	percpu_counter_dec(&EXT4_SB(inode->i_sb)->s_es_stats.es_stats_all_cnt);


	if (!ext4_es_is_delayed(es)) {
		BUG_ON(EXT4_I(inode)->i_es_shk_nr == 0);
		if (!--EXT4_I(inode)->i_es_shk_nr)
			ext4_es_list_del(inode);
		percpu_counter_dec(&EXT4_SB(inode->i_sb)->
					s_es_stats.es_stats_shk_cnt);
	}

	kmem_cache_free(ext4_es_cachep, es);
}

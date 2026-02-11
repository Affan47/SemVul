table_seq_next(struct seq_file *seq, void *iter_ptr, loff_t *pos)
{
	struct dlm_ls *ls = seq->private;
	struct rsbtbl_iter *ri = iter_ptr;
	struct rb_root *tree;
	struct rb_node *next;
	struct dlm_rsb *r, *rp;
	loff_t n = *pos;
	unsigned bucket;
	int toss = (seq->op == &format4_seq_ops);

	bucket = n >> 32;


	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	rp = ri->rsb;
	next = rb_next(&rp->res_hashnode);

	if (next) {
		r = rb_entry(next, struct dlm_rsb, res_hashnode);
		dlm_hold_rsb(r);
		ri->rsb = r;
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
		dlm_put_rsb(rp);
		++*pos;
		return ri;
	}
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	dlm_put_rsb(rp);


	n &= ~((1LL << 32) - 1);

	while (1) {
		bucket++;
		n += 1LL << 32;

		if (bucket >= ls->ls_rsbtbl_size) {
			kfree(ri);
			return NULL;
		}
		tree = toss ? &ls->ls_rsbtbl[bucket].toss : &ls->ls_rsbtbl[bucket].keep;

		spin_lock(&ls->ls_rsbtbl[bucket].lock);
		if (!RB_EMPTY_ROOT(tree)) {
			next = rb_first(tree);
			r = rb_entry(next, struct dlm_rsb, res_hashnode);
			dlm_hold_rsb(r);
			ri->rsb = r;
			ri->bucket = bucket;
			spin_unlock(&ls->ls_rsbtbl[bucket].lock);
			*pos = n;
			return ri;
		}
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	}
}

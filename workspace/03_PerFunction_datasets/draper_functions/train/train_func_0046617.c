aa_label_xprintk(struct aa_ns *ns, struct aa_label *label, int flags,
		      gfp_t gfp)
{
	AA_BUG(!label);

	if (!ns)
		ns = labels_ns(label);

	if (!use_label_hname(ns, label)) {
		char *str;
		int len;

		labelstats_inc(printk_name_alloc);
		len = aa_label_asxprint(&str, ns, label, flags, gfp);
		if (len == -1) {
			labelstats_inc(printk_name_fail);
			AA_DEBUG("label print error");
			return;
		}
		printk("%s", str);
		kfree(str);
	} else if (display_mode(ns, label, flags))
		printk("%s (%s)", label->hname,
		       label_modename(ns, label, flags));
	else
		printk("%s", label->hname);
}

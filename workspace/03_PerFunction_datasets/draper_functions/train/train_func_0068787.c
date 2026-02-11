VSC_Iter(struct VSM_data *vd, VSC_iter_f *func, void *priv)
{
	struct vsc *vsc = vsc_setup(vd);
	struct vsc_pt *pt;
	int i;

	if (1 != VSM_StillValid(vd, &vsc->iter_fantom)) {
		if (!VSM_Get(vd, &vsc->iter_fantom, VSC_CLASS, "", "")) {
			VSM_Close(vd);
			if (!vd->head && VSM_Open(vd))
				return (-1);
			if (!VSM_Get(vd, &vsc->iter_fantom, VSC_CLASS, "", ""))
				return (-1);
		}
		AN(vd->head);

		(void)func(priv, NULL);
		vsc_build_pt_list(vd);
		vsc_filter_pt_list(vd);
	}
	AN(vd->head);
	VTAILQ_FOREACH(pt, &vsc->pt_list, list) {
		i = func(priv, &pt->point);
		if (i)
			return (i);
	}
	return (0);
}

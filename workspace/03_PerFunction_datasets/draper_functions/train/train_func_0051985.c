cw1200_pm_stay_awake(struct cw1200_pm_state *pm,
			  unsigned long tmo)
{
	long cur_tmo;
	spin_lock_bh(&pm->lock);
	cur_tmo = pm->stay_awake.expires - jiffies;
	if (!timer_pending(&pm->stay_awake) || cur_tmo < (long)tmo)
		mod_timer(&pm->stay_awake, jiffies + tmo);
	spin_unlock_bh(&pm->lock);
}

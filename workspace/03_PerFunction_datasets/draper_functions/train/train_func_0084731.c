fixed_phy_update_state(struct phy_device *phydev,
			   const struct fixed_phy_status *status,
			   const struct fixed_phy_status *changed)
{
	struct fixed_mdio_bus *fmb = &platform_fmb;
	struct fixed_phy *fp;

	if (!phydev || phydev->bus != fmb->mii_bus)
		return -EINVAL;

	list_for_each_entry(fp, &fmb->phys, node) {
		if (fp->addr == phydev->addr) {
#define _UPD(x) if (changed->x) \
	fp->status.x = status->x
			_UPD(link);
			_UPD(speed);
			_UPD(duplex);
			_UPD(pause);
			_UPD(asym_pause);
#undef _UPD
			fixed_phy_update_regs(fp);
			return 0;
		}
	}

	return -ENOENT;
}

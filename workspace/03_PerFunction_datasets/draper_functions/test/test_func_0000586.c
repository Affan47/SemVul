ahci_platform_get_regulator(struct ahci_host_priv *hpriv, u32 port,
				struct device *dev)
{
	struct regulator *target_pwr;
	int rc = 0;

	target_pwr = regulator_get_optional(dev, "target");

	if (!IS_ERR(target_pwr))
		hpriv->target_pwrs[port] = target_pwr;
	else
		rc = PTR_ERR(target_pwr);

	return rc;
}

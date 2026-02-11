bq27xxx_battery_capacity_level(struct bq27xxx_device_info *di,
					  union power_supply_propval *val)
{
	int level;

	if (di->chip == BQ27000 || di->chip == BQ27010) {
		if (di->cache.flags & BQ27000_FLAG_FC)
			level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		else if (di->cache.flags & BQ27000_FLAG_EDV1)
			level = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		else if (di->cache.flags & BQ27000_FLAG_EDVF)
			level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		else
			level = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	} else {
		if (di->cache.flags & BQ27XXX_FLAG_FC)
			level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		else if (di->cache.flags & BQ27XXX_FLAG_SOC1)
			level = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		else if (di->cache.flags & BQ27XXX_FLAG_SOCF)
			level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		else
			level = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	}

	val->intval = level;

	return 0;
}

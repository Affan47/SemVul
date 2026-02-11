devm_regulator_match_supply_alias(struct device *dev, void *res,
					     void *data)
{
	struct regulator_supply_alias_match *match = res;
	struct regulator_supply_alias_match *target = data;

	return match->dev == target->dev && strcmp(match->id, target->id) == 0;
}

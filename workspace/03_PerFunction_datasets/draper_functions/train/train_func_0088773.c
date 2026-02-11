devm_region_match(struct device *dev, void *res, void *match_data)
{
	struct region_devres *this = res, *match = match_data;

	return this->parent == match->parent &&
		this->start == match->start && this->n == match->n;
}

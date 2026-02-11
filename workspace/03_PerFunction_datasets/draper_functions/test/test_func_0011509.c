read_field(struct tps6524x *hw, const struct field *field)
{
	int tmp;

	tmp = read_reg(hw, field->reg);
	if (tmp < 0)
		return tmp;

	return (tmp >> field->shift) & field->mask;
}

regmap_fields_force_write(struct regmap_field *field, unsigned int id,
			unsigned int val)
{
	if (id >= field->id_size)
		return -EINVAL;

	return regmap_write_bits(field->regmap,
				  field->reg + (field->id_offset * id),
				  field->mask, val << field->shift);
}

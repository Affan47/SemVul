to_supply(struct as3711_bl_data *su)
{
	switch (su->type) {
	case AS3711_BL_SU1:
		return container_of(su, struct as3711_bl_supply, su1);
	case AS3711_BL_SU2:
		return container_of(su, struct as3711_bl_supply, su2);
	}
	return NULL;
}

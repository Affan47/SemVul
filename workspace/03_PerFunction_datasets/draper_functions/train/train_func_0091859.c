gravity_split_xy_grav(
	int *ret_grav_x, int *ret_grav_y, int in_grav)
{
	switch (in_grav)
	{
	case NorthWestGravity:
	case WestGravity:
	case SouthWestGravity:
		*ret_grav_x = WestGravity;
		break;
	case NorthEastGravity:
	case EastGravity:
	case SouthEastGravity:
		*ret_grav_x = EastGravity;
		break;
	case NorthGravity:
	case CenterGravity:
	case SouthGravity:
	case ForgetGravity:
	case StaticGravity:
	default:
		*ret_grav_x = CenterGravity;
		break;
	}
	switch (in_grav)
	{
	case NorthWestGravity:
	case NorthGravity:
	case NorthEastGravity:
		*ret_grav_y = NorthGravity;
		break;
	case SouthWestGravity:
	case SouthGravity:
	case SouthEastGravity:
		*ret_grav_y = SouthGravity;
		break;
	case WestGravity:
	case CenterGravity:
	case EastGravity:
	case ForgetGravity:
	case StaticGravity:
	default:
		*ret_grav_y = CenterGravity;
		break;
	}
}

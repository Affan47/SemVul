setSpotLocation(icp, value, len, order, nest, op)
IMIC *icp;
char *value;
int len;
int order;
int nest;
int op;
{
    IMPSAttributes *ap;
    XPoint spot;

    TRACE(("imlib:setSpotLocation()\n"));

    CHECK_ICATTR_SIZE(4, IMBadSpotLocation);

    if (nest == NEST_STATUS) {
	DPRINT(("spot location specified in a status attribute list\n"));
	IMSendError(icp->im->connection, IMBadSpotLocation,
		    icp->im->id, icp->id,
		    "spot location isn't a status attribute");
	return -1;
    }

    ap = &icp->preedit_attr;

    spot.x = getI16(value, order);
    spot.y = getI16(value + 2, order);
    TRACE(("\tspot location: %d, %d\n", spot.x, spot.y));

    if (!(ap->set_mask & ATTR_MASK_SPOT_LOCATION) ||
	spot.x != ap->spot_location.x || spot.y != ap->spot_location.y) {
	ap->change_mask |= ATTR_MASK_SPOT_LOCATION;
    }
    ap->spot_location.x = spot.x;
    ap->spot_location.y = spot.y;
    ap->set_mask |= ATTR_MASK_SPOT_LOCATION;
    return 0;
}

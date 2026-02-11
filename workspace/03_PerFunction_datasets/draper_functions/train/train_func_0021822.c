anurbs_init(anim_nurbs *nurbs, u32 type, u32 nCtrl, u32 nKnots, Fixed *knots, u32 nWeight, Fixed *weights)
{
	memset(nurbs, 0, sizeof(anim_nurbs));
	nurbs->type = type;
	switch (type) {
	case ANIM_CUBIC:
		nurbs->npoints = 4;
		nurbs->nknots = 8;
		nurbs->knots = cubic_knots;
		break;
	case ANIM_QUADRATIC:
		nurbs->npoints = 3;
		nurbs->nknots = 6;
		nurbs->knots = quadratic_knots;
		break;
	default:
		nurbs->npoints = nCtrl;
		nurbs->knots = knots;
		nurbs->nknots = nKnots;
		nurbs->weights = weights;
		nurbs->nweights = nWeight;
		break;
	}
	nurbs->p = nurbs->nknots - nurbs->npoints - 1;
	if ((nurbs->p<=0) || (nurbs->p >= nurbs->nknots -1)
		|| ((nurbs->nweights>0) && (nurbs->npoints != nurbs->nweights)) ) {
		nurbs->valid = 0;
	} else {
		nurbs->valid = 1;
	}
}

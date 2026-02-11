getScaleSpaceMatrix(SbMatrix &mat, SbMatrix &inv) const


{
    SbMatrix	m;

    mat.makeIdentity();
    inv.makeIdentity();

    if (! scaleFactor.isIgnored() && ! scaleFactor.isDefault()) {
	SbVec3f	s = scaleFactor.getValue();
	SCALE(s, mat, inv, m);

        if (! scaleOrientation.isIgnored() && ! scaleOrientation.isDefault()) {
	    SbRotation	r = scaleOrientation.getValue();
	    r.invert();
	    ROTATE(r, mat, inv, m);
	}

    }
    if (! center.isIgnored() && ! center.isDefault()) {
	SbVec3f c = center.getValue();
	c.negate();
	TRANSLATE(c, mat, inv, m);
    }
}

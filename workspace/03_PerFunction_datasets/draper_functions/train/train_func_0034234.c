getMatrix(SoGetMatrixAction *action)


{
    if (! translation.isIgnored() && ! translation.isDefault()) {
	SbVec3f		v    = translation.getValue();
	SbMatrix	&ctm = action->getMatrix();
	SbMatrix	&inv = action->getInverse();
	SbMatrix	m;

	m.setTranslate(v);
	ctm.multLeft(m);
	m.setTranslate(-v);
	inv.multRight(m);
    }
}

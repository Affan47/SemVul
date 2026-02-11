clone() {
	GLELineDO* cl = new GLELineDO(getP1(), getP2());
	cl->setArrow(getArrow());
	return cl;
}

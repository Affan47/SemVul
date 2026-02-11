drawObj(TeXHashObject* hobj, TeXObjectInfo& info, GLERectangle* box) throw(ParserError) {

	if (!isEnabled()) {
		g_throw_parser_error("safe mode - TeX subsystem has been disabled");
	}

	info.initializeAll();

	double width = 1.0, height = 0.5, baseline = 0.1;
	if (hobj->hasDimensions()) {
		width = hobj->getWidth();
		height = hobj->getHeight();
		baseline = hobj->getBaseline();

	}

	double xp = info.getXp();
	double yp = info.getYp();
	int just = info.getJustify();
	g_dotjust(&xp, &yp, 0.0, width, height, 0.0, just);
	if ((just & 0x100) != 0) {
		yp -= baseline;
	}

	g_update_bounds(xp, yp+height);
	g_update_bounds(xp+width, yp);
	if (box != NULL) {
		box->setXMin(xp); box->setXMax(xp+width);
		box->setYMin(yp); box->setYMax(yp+height);
	}

	if ((info.getFlags() & TEX_OBJ_INF_DONT_PRINT) == 0 && !g_is_dummy_device()) {
		TeXObject* obj = new TeXObject();
		obj->setObject(hobj);
		obj->setXY(xp, yp);
		m_TeXObjects.push_back(obj);
		obj->setColor(info.getColor());

		double devx, devy;
		g_dev(xp, yp, &devx, &devy);
		obj->setDeviceXY(devx/PS_POINTS_PER_INCH*CM_PER_INCH, devy/PS_POINTS_PER_INCH*CM_PER_INCH);

		double angle = g_get_angle_deg();
		if (fabs(angle) > 1e-6) {
			obj->setAngle(angle);
		}

		return obj;
	} else {
		return NULL;
	}
}

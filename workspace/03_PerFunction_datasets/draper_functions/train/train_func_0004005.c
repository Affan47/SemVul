pov_textspan(GVJ_t * job, pointf c, textspan_t * span)
{
	double x, y;
	char *pov, *s, *r, *t, *p;

	gvprintf(job, "//*** textspan: %s, fontsize = %.3f, fontname = %s\n",
		 span->str, span->font->size, span->font->name);
	z = layerz - 9;

#ifdef DEBUG
	if (span->postscript_alias)
		gvputs(job, "// Warning: postscript_alias not handled!\n");
#endif


	switch (span->just) {
	case 'l':
		break;
	case 'r':
		c.x = c.x - span->size.x;
		break;
	default:
	case 'n':
		c.x = c.x - span->size.x / 2.0;
		break;
	}

	x = (c.x + job->translation.x) * job->scale.x;
	y = (c.y + job->translation.y) * job->scale.y;

	s = el(job, POV_SCALE1, span->font->size * job->scale.x);
	r = el(job, POV_ROTATE, 0.0, 0.0, (float)job->rotation);
	t = el(job, POV_TRANSLATE, x, y, z);
	p = pov_color_as_str(job, job->obj->pencolor, 0.0);


	pov = el(job, POV_TEXT "    %s    %s    %s    %s    %s" END,
		span->font->name, 0.25, 0.0,
		span->str, "    no_shadow\n", s, r, t, p);

#ifdef DEBUG
	GV_OBJ_EXT("Text", pov, span->str);
	gvprintf(job, "sphere{<0, 0, 0>, 2\ntranslate<%f, %f, %f>\n"
		 "pigment{color Red}\nno_shadow\n}\n", x, y, z - 1);
#else
	gvputs(job, pov);
#endif

	free(pov);
	free(r);
	free(p);
	free(t);
	free(s);
}

ToWebOOGL(QvState *state)
{
    ANNOUNCE(QvCone);
    OOGLout("# VRML Cone");
    OOGLout("{ = BEZ224");
    if (parts.value == ALL || parts.value == SIDES)
    {
      sprintf(out, "0 %f 0 1\t0 0 0 0\t0 %f 0 1", height.value/2.0,
	height.value/2.0);
      OOGLout(out);
      sprintf(out, "%f 0 0 1\t0 0 %f 0\t%f 0 0 1", -bottomRadius.value/2.0,
        bottomRadius.value/2.0, bottomRadius.value/2.0);
      OOGLout(out);
      sprintf(out, "%f %f 0 1\t0 0 %f 0\t%f %f 0 1\n", -bottomRadius.value,
        -height.value/2.0, bottomRadius.value, bottomRadius.value,
	-height.value/2.0);
      OOGLout(out);

      sprintf(out, "%f %f 0 1\t0 0 %f 0\t%f %f 0 1", -bottomRadius.value,
        -height.value/2.0, -bottomRadius.value, bottomRadius.value,
	-height.value/2.0);
      OOGLout(out);
      sprintf(out, "%f 0 0 1\t0 0 %f 0\t%f 0 0 1", -bottomRadius.value/2.0,
        -bottomRadius.value/2.0, bottomRadius.value/2.0);
      OOGLout(out);
      sprintf(out, "0 %f 0 1\t0 0 0 0\t0 %f 0 1\n", height.value/2.0,
	height.value/2.0);
      OOGLout(out);
    }
    if (parts.value == ALL || parts.value == BOTTOM)
    {
      sprintf(out, "0 %f 0 1\t0 0 0 0\t0 %f 0 1", -height.value/2.0,
        -height.value/2.0);
      OOGLout(out);
      sprintf(out, "%f %f 0 1\t0 0 %f 0\t%f %f 0 1", -bottomRadius.value/2.0,
        -height.value/2.0, bottomRadius.value/2.0,
        bottomRadius.value/2.0, -height.value/2.0);
      OOGLout(out);
      sprintf(out, "%f %f 0 1\t0 0 %f 0\t%f %f 0 1\n", -bottomRadius.value,
        -height.value/2.0, bottomRadius.value, bottomRadius.value,
	-height.value/2.0);
      OOGLout(out);

      sprintf(out, "%f %f 0 1\t0 0 %f 0\t%f %f 0 1", -bottomRadius.value,
        -height.value/2.0, -bottomRadius.value, bottomRadius.value,
	-height.value/2.0);
      OOGLout(out);
      sprintf(out, "%f %f 0 1\t0 0 %f 0\t%f %f 0 1", -bottomRadius.value/2.0,
        -height.value/2.0, -bottomRadius.value/2.0,
        bottomRadius.value/2.0, -height.value/2.0);
      OOGLout(out);
      sprintf(out, "0 %f 0 1\t0 0 0 0\t0 %f 0 1\n", -height.value/2.0,
        -height.value/2.0);
      OOGLout(out);
    }
    OOGLout("}");
}

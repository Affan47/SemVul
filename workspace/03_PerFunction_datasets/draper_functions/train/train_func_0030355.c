gl_label_object_get_size (glLabelObject *object,
			  gdouble       *w,
			  gdouble       *h)
{
	gl_debug (DEBUG_LABEL, "START");

	g_return_if_fail (object && GL_IS_LABEL_OBJECT (object));

	if ( GL_LABEL_OBJECT_GET_CLASS(object)->get_size != NULL )
        {

		GL_LABEL_OBJECT_GET_CLASS(object)->get_size (object, w, h);
	}
        else
        {
		gl_label_object_get_raw_size (object, w, h);
	}

	gl_debug (DEBUG_LABEL, "END");
}

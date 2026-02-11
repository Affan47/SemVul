action_camera_manual (GPParams *params)
{
	CameraText text;

	CR (gp_camera_get_manual (params->camera, &text, params->context));

	printf (_("Camera manual:"));
	printf ("\n%s\n", _(text.text));

	return (GP_OK);
}

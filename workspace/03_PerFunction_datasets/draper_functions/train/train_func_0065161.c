Nviz_has_focus(nv_data * data)
{
    float realto[3];

    if (GS_get_focus(realto))
	return 1;
    else
	return 0;
}

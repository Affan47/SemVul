gf_mo_resume(GF_MediaObject *mo)
{
#ifndef GPAC_DISABLE_VRML
	if (!mo || !mo->num_open || !mo->odm) return;
	mediacontrol_resume(mo->odm);
#endif
}

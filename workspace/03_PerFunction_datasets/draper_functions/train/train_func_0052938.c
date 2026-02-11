VCL_Poll(void)
{
	struct vcls *vcl, *vcl2;

	ASSERT_CLI();
	VTAILQ_FOREACH_SAFE(vcl, &vcl_head, list, vcl2)
		if (vcl->conf->discard && vcl->conf->busy == 0)
			VCL_Nuke(vcl);
}

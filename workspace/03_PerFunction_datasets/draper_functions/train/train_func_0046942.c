xicc_dump_viewcond(
icxViewCond *vc
) {
	printf("Viewing Condition:\n");
	if (vc->Ev == vc_dark)
		printf("  Surround to Image: Dark\n");
	else if (vc->Ev == vc_dim)
		printf("  Surround to Image: Dim\n");
	else if (vc->Ev == vc_average)
		printf("  Surround to Image: Average\n");
	else if (vc->Ev == vc_cut_sheet)
		printf("  Transparency on Light box\n");
	printf("  Adapted white = %f %f %f\n",vc->Wxyz[0], vc->Wxyz[1], vc->Wxyz[2]);
	printf("  Adapted luminance = %f cd/m^2\n",vc->La);
	printf("  Background to image ratio = %f\n",vc->Yb);
	if (vc->Ev == vc_none)
		printf("  Image luminance = %f cd/m^2\n",vc->Lv);
	printf("  Flare to image ratio = %f\n",vc->Yf);
	printf("  Flare color = %f %f %f\n",vc->Fxyz[0], vc->Fxyz[1], vc->Fxyz[2]);
}

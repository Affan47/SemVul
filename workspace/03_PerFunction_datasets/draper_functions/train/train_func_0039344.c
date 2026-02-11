defg1(void)
{
	setg(0);
	fputs("<g", fout);
	if (gcur.xscale != 1 || gcur.yscale != 1 || gcur.rotate != 0) {
		fprintf(fout, " transform=\"");
		if (gcur.xscale != 1 || gcur.yscale != 1) {
			if (gcur.xscale == gcur.yscale)
				fprintf(fout, "scale(%.3f)", gcur.xscale);
			else
				fprintf(fout, "scale(%.3f,%.3f)",
						gcur.xscale, gcur.yscale);
		}
		if (gcur.rotate != 0) {
			if (xoffs != 0 || yoffs != 0) {
				fprintf(fout, " translate(%.2f, %.2f)",
						xoffs, yoffs);
				x_rot = xoffs;
				y_rot = yoffs;
				xoffs = 0;
				yoffs = 0;
			}
			fprintf(fout, " rotate(%.2f)",
					gcur.rotate);
		}
		fputs("\"", fout);
	}
	if (gcur.linewidth != 1)
		fprintf(fout, " stroke-width=\"%.2f\"", gcur.linewidth);
	selfont(0);
	if (gcur.rgb != 0)
		fprintf(fout, " style=\"color:#%06x;fill:#%06x\"",
				gcur.rgb, gcur.rgb);
	fprintf(fout, "%s>\n", gcur.dash);
	g = 1;
	memcpy(&gold, &gcur, sizeof gold);
}
